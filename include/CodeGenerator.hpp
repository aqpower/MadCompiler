#ifndef INTERMEDIATE_CODE_GENERATOR_H
#define INTERMEDIATE_CODE_GENERATOR_H

#include "ast.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Compiler {

struct Quadruple {
    std::string op;
    std::string arg1;
    std::string arg2;
    std::string result;

    Quadruple(
        const std::string &op,
        const std::string &arg1,
        const std::string &arg2,
        const std::string &result)
        : op(op), arg1(arg1), arg2(arg2), result(result) {}
};

class IntermediateCodeGenerator {
  public:
    void generate(const std::unique_ptr<ASTNode> &ast);
    void print() const;

  private:
    std::vector<Quadruple> code;
    void visit(const ASTNode &node);
    void visit(const AssignNode &node);
    void visit(const ExprNode &node);
    void visit(const IdentifierNode &node);
    void visit(const NumberNode &node);
    void visit(const IfNode &node);
    void visit(const IfElseNode &node);
    void visit(const WhileNode &node);
    void visit(const CompoundStmtNode &node);

    std::string newTemp();
    std::string getTempName();

    int tempCount = 0;
    std::unordered_map<const ASTNode *, std::string> tempMap;
};

} // namespace Compiler

#endif // INTERMEDIATE_CODE_GENERATOR_H
