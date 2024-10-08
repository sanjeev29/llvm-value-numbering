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
