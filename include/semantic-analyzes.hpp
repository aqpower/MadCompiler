#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "ast.hpp"

namespace Compiler {

class SemanticAnalyzer {
  public:
    void analyze(const std::unique_ptr<ASTNode> &root);

  private:
    void analyzeNode(const std::unique_ptr<ASTNode> &node);
    // 其他语义分析相关的私有成员函数
};

} // namespace Compiler

#endif // SEMANTIC_ANALYZER_H
