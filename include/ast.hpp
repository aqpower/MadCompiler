#ifndef AST_H
#define AST_H

#include "token.hpp"
#include <memory>

namespace Compiler {

class ASTNode {
  public:
    virtual ~ASTNode() = default;
    virtual void print(int indent = 0) const = 0;
};

class EmptyNode : public ASTNode {
  public:
    void print(int indent = 0) const override;
};

class IdentifierNode : public ASTNode {
  public:
    explicit IdentifierNode(Token id);

    Token id; // id means identifier
    
    void print(int indent = 0) const override;
};

class ExprNode : public ASTNode {
  public:
    ExprNode(std::unique_ptr<ASTNode> left, Token op, std::unique_ptr<ASTNode> right);
    
    std::unique_ptr<ASTNode> left;
    Token op;
    std::unique_ptr<ASTNode> right;
    
    void print(int indent = 0) const override;
};

class NumberNode : public ASTNode {
  public:
    explicit NumberNode(Token value);
    
    Token value;
    
    void print(int indent = 0) const override;
};

// id = expr;
class AssignNode : public ASTNode {
  public:
    AssignNode(Token id, std::unique_ptr<ASTNode> value);
    
    Token id;
    std::unique_ptr<ASTNode> value;
    
    void print(int indent = 0) const override;
};

// stmts -> stmt stmts 
class CompoundStmtNode : public ASTNode {
  public:
    CompoundStmtNode(std::unique_ptr<ASTNode> first, std::unique_ptr<ASTNode> second);
    
    std::unique_ptr<ASTNode> first;
    std::unique_ptr<ASTNode> second;
    
    void print(int indent = 0) const override;
};

class IfNode : public ASTNode {
  public:
    IfNode(std::unique_ptr<ASTNode> condition, std::unique_ptr<ASTNode> thenStmt);
    
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<ASTNode> thenStmt;
    
    void print(int indent = 0) const override;
};

class IfElseNode : public ASTNode {
  public:
    IfElseNode(
        std::unique_ptr<ASTNode> condition,
        std::unique_ptr<ASTNode> thenStmt,
        std::unique_ptr<ASTNode> elseStmt);
    
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<ASTNode> thenStmt;
    std::unique_ptr<ASTNode> elseStmt;
    
    void print(int indent = 0) const override;
};

class WhileNode : public ASTNode {
  public:
    WhileNode(std::unique_ptr<ASTNode> condition, std::unique_ptr<ASTNode> body);
    
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<ASTNode> body;
    
    void print(int indent = 0) const override;
};

} // namespace Compiler

#endif // AST_H
