#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "ast.hpp"
#include <memory>
#include <string>
#include <unordered_map>

namespace Compiler {

class SemanticAnalyzer {
  public:
    void analyze(const std::unique_ptr<ASTNode> &ast);

  private:
    std::unordered_map<std::string, std::string> symbolTable; // 符号表
    void visit(const ASTNode &node);
    void visit(const IdentifierNode &node);
    void visit(const NumberNode &node);
    void visit(const AssignNode &node);
    void visit(const ExprNode &node);
    void visit(const IfNode &node);
    void visit(const IfElseNode &node);
    void visit(const WhileNode &node);
    void visit(const CompoundStmtNode &node);
};

} // namespace Compiler

#endif // SEMANTIC_ANALYZER_H
