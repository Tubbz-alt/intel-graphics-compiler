/*===================== begin_copyright_notice ==================================

Copyright (c) 2017 Intel Corporation

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


======================= end_copyright_notice ==================================*/
//
/// GenXGlobalVariableLowering
/// --------------------------
/// In vISA relocations are enabled via faddr instruction:
/// faddr very_important_data V1(0,0)<1>
/// For global variable symbols LLVM IR represintation of this instruction is:
/// %g = call i64 @llvm.genx.gaddr.i64.p0a8i8([8 x i8]* @very_important_data)
/// The goal of this lowering pass is to make every user of a global variable
/// llvm.genx.gaddr intrinsic.
/// For example:
/// store <2 x [8 x i32]*> <[8 x i32]* @array_a, [8 x i32]* @array_b>,
///       <2 x [8 x i32]*>* %ptr
/// Becomes:
/// %array_a.gaddr = call i64 @llvm.genx.gaddr.i64.p0a8i32([8 x i32]* @array_a)
/// %array_a.lowered = inttoptr i64 %array_a.gaddr to [8 x i32]*
/// %array_b.gaddr = call i64 @llvm.genx.gaddr.i64.p0a8i32([8 x i32]* @array_b)
/// %array_b.lowered = inttoptr i64 %array_b.gaddr to [8 x i32]*
/// %vec.half = insertelement <2 x [8 x i32]*> undef,
///                           [8 x i32]* %array_a.lowered, i64 0
/// %vec = insertelement <2 x [8 x i32]*> %vec.half,
///                      [8 x i32]* %array_b.lowered, i64 1
/// store <2 x [8 x i32]*> %vec, <2 x [8 x i32]*>* %ptr
///
//===----------------------------------------------------------------------===//

#include "GenX.h"
#include "GenXUtil.h"

#include "Probe/Assertion.h"

#include <llvm/GenXIntrinsics/GenXIntrinsics.h>

#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/Pass.h>

#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace llvm;

namespace {

// Cannot use llvm::Use here as uses will change during the construction.
// Plus some helper methods for covenience.
struct UserInfo {
  Instruction *Inst;
  unsigned OperandNo;

  Value *getOperand() const { return Inst->getOperand(OperandNo); }
  Use &getOperandUse() const { return Inst->getOperandUse(OperandNo); }
  Constant *getConstOperand() const { return cast<Constant>(getOperand()); }

  friend bool operator==(const UserInfo &LHS, const UserInfo &RHS) {
    return LHS.Inst == RHS.Inst && LHS.OperandNo == RHS.OperandNo;
  }
};
} // anonymous namespace

template <> struct std::hash<UserInfo> {
  std::size_t operator()(const UserInfo &Usr) const {
    return std::hash<Instruction *>{}(Usr.Inst) ^
           std::hash<unsigned>{}(Usr.OperandNo);
  }
};

namespace {

class GenXGlobalVariableLowering : public ModulePass {
  using FuncConstantReplacementMap = std::unordered_map<Constant *, Value *>;
  using FuncConstantUsersSet = std::unordered_set<UserInfo>;
  struct FuncConstantLoweringInfo {
    FuncConstantReplacementMap Replacement;
    FuncConstantUsersSet Users;
  };
  using ModuleConstantLoweringInfo =
      std::unordered_map<Function *, FuncConstantLoweringInfo>;

  const DataLayout *DL = nullptr;
  ModuleConstantLoweringInfo WorkList;

public:
  static char ID;
  explicit GenXGlobalVariableLowering() : ModulePass(ID) {}
  StringRef getPassName() const override {
    return "GenX global variable lowering";
  }
  void getAnalysisUsage(AnalysisUsage &AU) const override;
  bool runOnModule(Module &M) override;

private:
  void fillWorkListForGV(GlobalVariable &GV);
  void fillWorkListForGVUse(Use &GVUse);
  void fillWorkListForGVInstUse(Use &GVUse);
  void fillWorkListForGVConstUse(Use &GVUse);
  void buildAllConstantReplacementsInFunction(Function &Func);
  Value *buildConstantReplacement(Constant &Const, IRBuilder<> &Builder,
                                  Function &Func);
  Instruction *buildGVReplacement(GlobalVariable &Const, IRBuilder<> &Builder,
                                  Function &Func);
  Value *buildConstAggrReplacement(ConstantAggregate &ConstAggr,
                                   IRBuilder<> &Builder, Function &Func);
  Value *buildConstExprReplacement(ConstantExpr &ConstExpr,
                                   IRBuilder<> &Builder, Function &Func);
  void updateUsers(Function &Func);
};

} // end namespace

char GenXGlobalVariableLowering::ID = 0;
namespace llvm {
void initializeGenXGlobalVariableLoweringPass(PassRegistry &);
}

INITIALIZE_PASS_BEGIN(GenXGlobalVariableLowering, "GenXGlobalVariableLowering",
                      "GenXGlobalVariableLowering", false, false)
INITIALIZE_PASS_END(GenXGlobalVariableLowering, "GenXGlobalVariableLowering",
                    "GenXGlobalVariableLowering", false, false)

ModulePass *llvm::createGenXGlobalVariableLoweringPass() {
  initializeGenXGlobalVariableLoweringPass(*PassRegistry::getPassRegistry());
  return new GenXGlobalVariableLowering;
}

void GenXGlobalVariableLowering::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesCFG();
}

bool GenXGlobalVariableLowering::runOnModule(Module &M) {
  DL = &M.getDataLayout();
  for (auto &GV : M.globals())
    fillWorkListForGV(GV);

  if (WorkList.empty())
    return false;

  for (auto &FuncInfo : WorkList) {
    buildAllConstantReplacementsInFunction(*FuncInfo.first);
    updateUsers(*FuncInfo.first);
  }

  return true;
}

void GenXGlobalVariableLowering::fillWorkListForGV(GlobalVariable &GV) {
  if (!genx::isRealGlobalVariable(GV))
    return;
  for (Use &GVUse : GV.uses())
    fillWorkListForGVUse(GVUse);
}

// Only constants that are directly used in an instruction are added to
// replacement map. Other constants aren't added during this phase as
// it is hard to define in which fuction they are used, until instruction
// user is met.
void GenXGlobalVariableLowering::fillWorkListForGVUse(Use &GVUse) {
  User *Usr = GVUse.getUser();
  if (isa<Instruction>(Usr)) {
    fillWorkListForGVInstUse(GVUse);
    return;
  }
  IGC_ASSERT_MESSAGE(isa<Constant>(Usr), "unexpected global variable user");
  fillWorkListForGVConstUse(GVUse);
}

static Instruction *buildGaddr(IRBuilder<> &Builder, GlobalVariable &GV) {
  Module *M = GV.getParent();
  Type *IntPtrTy = M->getDataLayout().getIntPtrType(Builder.getContext());
  Function *GAddrDecl = GenXIntrinsic::getGenXDeclaration(
      M, llvm::GenXIntrinsic::genx_gaddr, {IntPtrTy, GV.getType()});
  return Builder.CreateCall(GAddrDecl->getFunctionType(), GAddrDecl, &GV,
                            GV.getName() + ".gaddr");
}

void GenXGlobalVariableLowering::fillWorkListForGVInstUse(Use &GVUse) {
  auto *Usr = cast<Instruction>(GVUse.getUser());
  auto *ConstWithGV = cast<Constant>(GVUse.get());
  IGC_ASSERT_MESSAGE(GenXIntrinsic::getAnyIntrinsicID(Usr) !=
                         GenXIntrinsic::genx_gaddr,
                     "llvm.gaddr must be inserted by this pass, but someone "
                     "inserted it before");
  Function *Func = Usr->getParent()->getParent();
  WorkList[Func].Users.insert({Usr, GVUse.getOperandNo()});
  WorkList[Func].Replacement[ConstWithGV] = nullptr;
}

// For constant use continue recursively travers through users, until
// instruction user is met.
void GenXGlobalVariableLowering::fillWorkListForGVConstUse(Use &GVUse) {
  auto *Usr = cast<Constant>(GVUse.getUser());
  for (Use &U : Usr->uses())
    fillWorkListForGVUse(U);
}

// Build all the instruction that will replace constant uses in the provided
// function. All the instructions are inserted at the function entry.
void GenXGlobalVariableLowering::buildAllConstantReplacementsInFunction(
    Function &Func) {
  auto &ConstantsInfo = WorkList[&Func];
  // Have to copy the original set of constants as replacement map will change
  // during the construction.
  std::vector<Constant *> Constants;
  std::transform(ConstantsInfo.Replacement.begin(),
                 ConstantsInfo.Replacement.end(), std::back_inserter(Constants),
                 [](FuncConstantReplacementMap::value_type &ReplacementInfo) {
                   return ReplacementInfo.first;
                 });
  IRBuilder<> Builder{&*Func.getEntryBlock().getFirstInsertionPt()};
  for (Constant *Const : Constants)
    buildConstantReplacement(*Const, Builder, Func);
}

Value *GenXGlobalVariableLowering::buildConstantReplacement(
    Constant &Const, IRBuilder<> &Builder, Function &Func) {
  if (WorkList[&Func].Replacement.count(&Const) &&
      WorkList[&Func].Replacement.at(&Const))
    // the constant already has a replacement
    return WorkList[&Func].Replacement.at(&Const);

  if (isa<GlobalVariable>(Const))
    return buildGVReplacement(cast<GlobalVariable>(Const), Builder, Func);
  if (isa<ConstantAggregate>(Const))
    return buildConstAggrReplacement(cast<ConstantAggregate>(Const), Builder,
                                     Func);
  if (isa<ConstantExpr>(Const))
    return buildConstExprReplacement(cast<ConstantExpr>(Const), Builder, Func);
  // The rest of constants cannot have global variables as part of them.
  return &Const;
}

// Global variable is replaced with pair of gaddr + inttoptr:
//    %a.gaddr = call i64 @llvm.genx.gaddr.i64.p0a8i32([8 x i32]* @a)
//    %a.lowered = inttoptr i64 %a.gaddr to [8 x i32]*
Instruction *GenXGlobalVariableLowering::buildGVReplacement(
    GlobalVariable &GV, IRBuilder<> &Builder, Function &Func) {
  IGC_ASSERT_MESSAGE(WorkList[&Func].Replacement.count(&GV) == 0 ||
                         !WorkList[&Func].Replacement[&GV],
                     "the constant shouldn't have a replacement already");
  auto *Gaddr = buildGaddr(Builder, GV);
  auto *GVReplacement = cast<Instruction>(
      Builder.CreateIntToPtr(Gaddr, GV.getType(), GV.getName() + ".lowered"));
  // May create a new map entry here.
  WorkList[&Func].Replacement[&GV] = GVReplacement;
  return GVReplacement;
}

Value *GenXGlobalVariableLowering::buildConstAggrReplacement(
    ConstantAggregate &ConstAggr, IRBuilder<> &Builder, Function &Func) {
  Value *Replacement = UndefValue::get(ConstAggr.getType());
  for (auto IndexedOp : enumerate(ConstAggr.operands())) {
    auto *OpReplacement = buildConstantReplacement(
        *cast<Constant>(IndexedOp.value().get()), Builder, Func);

    if (isa<ConstantVector>(ConstAggr)) {
      Replacement = Builder.CreateInsertElement(
          Replacement, OpReplacement, IndexedOp.index(), "gaddr.lowering");
      continue;
    }
    Replacement = Builder.CreateInsertValue(
        Replacement, OpReplacement, IndexedOp.index(), "gaddr.lowering");
  }
  // May create a new map entry here.
  WorkList[&Func].Replacement[&ConstAggr] = Replacement;
  return Replacement;
}

Value *GenXGlobalVariableLowering::buildConstExprReplacement(
    ConstantExpr &ConstExpr, IRBuilder<> &Builder, Function &Func) {
  std::vector<Value *> NewOps;
  std::transform(ConstExpr.op_begin(), ConstExpr.op_end(),
                 std::back_inserter(NewOps), [this, &Builder, &Func](Use &U) {
                   return buildConstantReplacement(*cast<Constant>(U.get()),
                                                   Builder, Func);
                 });
  Instruction *Replacement = ConstExpr.getAsInstruction();
  // set new operands
  std::copy(NewOps.begin(), NewOps.end(), Replacement->op_begin());
  Replacement->insertBefore(&*Builder.GetInsertPoint());
  Replacement->setName("gaddr.lowering");
  // May create a new map entry here.
  WorkList[&Func].Replacement[&ConstExpr] = Replacement;
  return Replacement;
}

// When all replacing instructions are generated, this method
// just replaces const operands with generated instructions.
void GenXGlobalVariableLowering::updateUsers(Function &Func) {
  auto &ConstantsInfo = WorkList[&Func];
  std::unordered_set<Instruction *> PotentialToErase;
  std::vector<Instruction *> ToErase;

  for (UserInfo Usr : ConstantsInfo.Users) {
    Instruction *ConstReplacement =
        cast<Instruction>(ConstantsInfo.Replacement[Usr.getConstOperand()]);
    IGC_ASSERT_MESSAGE(ConstReplacement, "no replacement was generated");
    if (isa<PtrToIntInst>(Usr.Inst) && isa<IntToPtrInst>(ConstReplacement) &&
        Usr.Inst->getType() == ConstReplacement->getOperand(0)->getType()) {
      // can optimize here
      Usr.Inst->replaceAllUsesWith(ConstReplacement->getOperand(0));
      ToErase.push_back(Usr.Inst);
      PotentialToErase.insert(ConstReplacement);
      continue;
    }
    Usr.getOperandUse() = ConstReplacement;
  }

  for (Instruction *Inst : ToErase)
    Inst->eraseFromParent();
  for (Instruction *Inst : PotentialToErase)
    if (Inst->use_empty())
      Inst->eraseFromParent();
}
