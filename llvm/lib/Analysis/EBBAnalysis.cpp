#include "llvm/Analysis/EBBAnalysis.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Pass.h"

using namespace llvm;

AnalysisKey EBBAnalysis::Key;

EBBAnalysis::Result EBBAnalysis::run(Function &F, FunctionAnalysisManager &AM) {
  Result EBBs;
  std::vector<BasicBlock*> currentEBB;


    for (BasicBlock &BB : F) {
      if (currentEBB.empty() || BB.getSinglePredecessor() == currentEBB.back()) {
        currentEBB.push_back(&BB);
      } else {
        if (!currentEBB.empty()) {
          EBBs.push_back(currentEBB);
          currentEBB.clear();
        }
        currentEBB.push_back(&BB);
      }
    }

  if (!currentEBB.empty()) {
    EBBs.push_back(currentEBB);
  }

  return EBBs;
}

// Legacy pass implementation
namespace {
class EBBAnalysisLegacyPass : public FunctionPass {
public:
  static char ID;
  EBBAnalysisLegacyPass() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
    // This is an analysis pass, so always return false as we're not
    // transforming the function
    return false;
  }

  void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.setPreservesAll();
  }
};
}

char EBBAnalysisLegacyPass::ID = 0;
static RegisterPass<EBBAnalysisLegacyPass>
    X("ebb-analysis", "Extended Basic Block Analysis", false, true);

// Public interface to the EBBAnalysis pass
FunctionPass *llvm::createEBBAnalysisPass() {
  return new EBBAnalysisLegacyPass();
}
