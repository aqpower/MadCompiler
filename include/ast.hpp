#ifndef AST_H
#define AST_H

#include "token.hpp"
#include <memory>

namespace Compiler {

class ASTNode {
  public:
    virtual ~ASTNode() = default;
};

class ExprNode : public ASTNode {
  public:
    ExprNode(std::unique_ptr<ASTNode> left, Token op, std::unique_ptr<ASTNode> right);
    std::unique_ptr<ASTNode> left;
    Token op;
    std::unique_ptr<ASTNode> right;
};

class NumberNode : public ASTNode {
  public:
    explicit NumberNode(Token value);
    Token value;
};

// 其他AST节点类...

} // namespace Compiler

#endif // AST_H
