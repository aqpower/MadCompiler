#include "SemanticAnalyzer.hpp"
#include "CodeGenerator.hpp"
#include <iostream>
#include <vector>

namespace Compiler {

void SemanticAnalyzer::analyze(const std::unique_ptr<ASTNode> &ast) {
    if (ast) { visit(*ast); }
}

const std::vector<Quadruple> &IntermediateCodeGenerator::getCode() const {
    return code;
}

void SemanticAnalyzer::visit(const ASTNode &node) {
    if (auto compoundNode = dynamic_cast<const CompoundStmtNode *>(&node)) {
        visit(*compoundNode);
    } else if (auto ifNode = dynamic_cast<const IfNode *>(&node)) {
        visit(*ifNode);
    } else if (auto ifElseNode = dynamic_cast<const IfElseNode *>(&node)) {
        visit(*ifElseNode);
    } else if (auto whileNode = dynamic_cast<const WhileNode *>(&node)) {
        visit(*whileNode);
    } else if (auto assignNode = dynamic_cast<const AssignNode *>(&node)) {
        visit(*assignNode);
    } else if (auto exprNode = dynamic_cast<const ExprNode *>(&node)) {
        visit(*exprNode);
    } else if (auto idNode = dynamic_cast<const IdentifierNode *>(&node)) {
        visit(*idNode);
    } else if (auto numNode = dynamic_cast<const NumberNode *>(&node)) {
        visit(*numNode);
    } else if (auto emptyNode = dynamic_cast<const EmptyNode *>(&node)) {
        // emptyNode->print();
    } else {
        std::cerr << "Unrecognized AST node type." << std::endl;
    }
}

void SemanticAnalyzer::visit(const CompoundStmtNode &node) {
    // std::cout << "Visiting CompoundStmtNode" << std::endl;
    visit(*node.first);
    if (node.second) { visit(*node.second); }
}

void SemanticAnalyzer::visit(const IfNode &node) {
    // std::cout << "Visiting IfNode" << std::endl;
    visit(*node.condition);
    visit(*node.thenStmt);
}

void SemanticAnalyzer::visit(const IfElseNode &node) {
    // std::cout << "Visiting IfElseNode" << std::endl;
    visit(*node.condition);
    visit(*node.thenStmt);
    visit(*node.elseStmt);
}

void SemanticAnalyzer::visit(const WhileNode &node) {
    // std::cout << "Visiting WhileNode" << std::endl;
    visit(*node.condition);
    visit(*node.body);
}

void SemanticAnalyzer::visit(const AssignNode &node) {
    // std::cout << "Visiting AssignNode" << std::endl;
    if (symbolTable.find(node.id.value) == symbolTable.end()) {
        std::cerr << "错误: 未声明的变量 " << node.id.value << std::endl;
    }
    visit(*node.value);
}

void SemanticAnalyzer::visit(const ExprNode &node) {
    // std::cout << "Visiting ExprNode" << std::endl;
    visit(*node.left);
    visit(*node.right);
}

void SemanticAnalyzer::visit(const IdentifierNode &node) {
    // std::cout << "Visiting IdentifierNode(" << node.id.value << ")" << std::endl;
    if (symbolTable.find(node.id.value) == symbolTable.end()) {
        symbolTable[node.id.value] = "int"; // 假设所有变量都是 int 类型
    }
}

void SemanticAnalyzer::visit(const NumberNode &node) {
    // std::cout << "Visiting NumberNode(" << node.value.value << ")" << std::endl;
}

} // namespace Compiler
