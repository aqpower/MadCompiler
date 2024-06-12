#include "ast.hpp"
#include <iostream>

namespace Compiler {

void printIndent(int indent) {
    for (int i = 0; i < indent; ++i) { std::cout << "  "; }
}

void EmptyNode::print(int indent) const {
    printIndent(indent);
    std::cout << "EmptyNode" << std::endl;
}

IdentifierNode::IdentifierNode(Token id) : id(id) {
}

void IdentifierNode::print(int indent) const {
    printIndent(indent);
    std::cout << "IdentifierNode(" << id.value << ")" << std::endl;
}

ExprNode::ExprNode(std::unique_ptr<ASTNode> left, Token op, std::unique_ptr<ASTNode> right)
    : left(std::move(left)), op(op), right(std::move(right)) {
}

void ExprNode::print(int indent) const {
    printIndent(indent);
    std::cout << "ExprNode(" << op.value << ")" << std::endl;
    left->print(indent + 1);
    right->print(indent + 1);
}

NumberNode::NumberNode(Token value) : value(value) {
}

void NumberNode::print(int indent) const {
    printIndent(indent);
    std::cout << "NumberNode(" << value.value << ")" << std::endl;
}

AssignNode::AssignNode(Token id, std::unique_ptr<ASTNode> value)
    : id(id), value(std::move(value)) {
}

void AssignNode::print(int indent) const {
    printIndent(indent);
    std::cout << "AssignNode(" << id.value << ")" << std::endl;
    value->print(indent + 1);
}

CompoundStmtNode::CompoundStmtNode(
    std::unique_ptr<ASTNode> first, std::unique_ptr<ASTNode> second)
    : first(std::move(first)), second(std::move(second)) {
}

void CompoundStmtNode::print(int indent) const {
    printIndent(indent);
    std::cout << "CompoundStmtNode" << std::endl;
    first->print(indent + 1);
    if (second) { second->print(indent + 1); }
}

IfNode::IfNode(std::unique_ptr<ASTNode> condition, std::unique_ptr<ASTNode> thenStmt)
    : condition(std::move(condition)), thenStmt(std::move(thenStmt)) {
}

void IfNode::print(int indent) const {
    printIndent(indent);
    std::cout << "IfNode" << std::endl;
    condition->print(indent + 1);
    thenStmt->print(indent + 1);
}

IfElseNode::IfElseNode(
    std::unique_ptr<ASTNode> condition,
    std::unique_ptr<ASTNode> thenStmt,
    std::unique_ptr<ASTNode> elseStmt)
    : condition(std::move(condition))
    , thenStmt(std::move(thenStmt))
    , elseStmt(std::move(elseStmt)) {
}

void IfElseNode::print(int indent) const {
    printIndent(indent);
    std::cout << "IfElseNode" << std::endl;
    condition->print(indent + 1);
    thenStmt->print(indent + 1);
    elseStmt->print(indent + 1);
}

WhileNode::WhileNode(std::unique_ptr<ASTNode> condition, std::unique_ptr<ASTNode> body)
    : condition(std::move(condition)), body(std::move(body)) {
}

void WhileNode::print(int indent) const {
    printIndent(indent);
    std::cout << "WhileNode" << std::endl;
    condition->print(indent + 1);
    body->print(indent + 1);
}

} // namespace Compiler
