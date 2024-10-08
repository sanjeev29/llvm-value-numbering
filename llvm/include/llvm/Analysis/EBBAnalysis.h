#ifndef LLVM_ANALYSIS_EBBANALYSIS_H
#define LLVM_ANALYSIS_EBBANALYSIS_H

#include "llvm/Pass.h"
#include "llvm/IR/PassManager.h"
#include <vector>

namespace llvm {

class Function;
class BasicBlock;

class EBBAnalysis : public AnalysisInfoMixin<EBBAnalysis> {
public:
  using Result = std::vector<std::vector<BasicBlock*>>;
  Result run(Function &F, FunctionAnalysisManager &AM);

private:
  friend struct AnalysisInfoMixin<EBBAnalysis>;
  static AnalysisKey Key;
};

/// Create a legacy EBBAnalysis pass.
FunctionPass *createEBBAnalysisPass();

} // end namespace llvm

#endif // LLVM_ANALYSIS_EBBANALYSIS_H
