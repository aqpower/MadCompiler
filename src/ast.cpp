#include "ast.hpp"
#include <iostream>
#include <utility>

namespace Compiler {

void EmptyNode::print() const {
    // 空节点不打印任何内容
}

IdentifierNode::IdentifierNode(Token id) : id(std::move(id)) {
}

void IdentifierNode::print() const {
    std::cout << id.value;
}

ExprNode::ExprNode(std::unique_ptr<ASTNode> left, Token op, std::unique_ptr<ASTNode> right)
    : left(std::move(left)), op(op), right(std::move(right)) {
}

void ExprNode::print() const {
    std::cout << "(";
    left->print();
    std::cout << " " << op.value << " ";
    right->print();
    std::cout << ")";
}

NumberNode::NumberNode(Token value) : value(std::move(value)) {
}

void NumberNode::print() const {
    std::cout << value.value;
}

AssignNode::AssignNode(Token id, std::unique_ptr<ASTNode> value)
    : id(std::move(id)), value(std::move(value)) {
}

void AssignNode::print() const {
    std::cout << id.value << " = ";
    value->print();
    std::cout << ";";
}

CompoundStmtNode::CompoundStmtNode(
    std::unique_ptr<ASTNode> first, std::unique_ptr<ASTNode> second)
    : first(std::move(first)), second(std::move(second)) {
}

void CompoundStmtNode::print() const {
    first->print();
    std::cout << " ";
    second->print();
}

IfNode::IfNode(std::unique_ptr<ASTNode> condition, std::unique_ptr<ASTNode> thenStmt)
    : condition(std::move(condition)), thenStmt(std::move(thenStmt)) {
}

void IfNode::print() const {
    std::cout << "if (";
    condition->print();
    std::cout << ") ";
    thenStmt->print();
}

IfElseNode::IfElseNode(
    std::unique_ptr<ASTNode> condition,
    std::unique_ptr<ASTNode> thenStmt,
    std::unique_ptr<ASTNode> elseStmt)
    : condition(std::move(condition))
    , thenStmt(std::move(thenStmt))
    , elseStmt(std::move(elseStmt)) {
}

void IfElseNode::print() const {
    std::cout << "if (";
    condition->print();
    std::cout << ") ";
    thenStmt->print();
    std::cout << " else ";
    elseStmt->print();
}

WhileNode::WhileNode(std::unique_ptr<ASTNode> condition, std::unique_ptr<ASTNode> body)
    : condition(std::move(condition)), body(std::move(body)) {
}

void WhileNode::print() const {
    std::cout << "while (";
    condition->print();
    std::cout << ") ";
    body->print();
}

} // namespace Compiler
