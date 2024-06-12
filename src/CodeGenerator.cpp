#include "CodeGenerator.hpp"
#include <iostream>

namespace Compiler {

void IntermediateCodeGenerator::generate(const std::unique_ptr<ASTNode> &ast) {
    if (ast) { visit(*ast); }
}

void IntermediateCodeGenerator::print() const {
    for (const auto &quad : code) {
        std::cout << "(" << quad.op << ", " << quad.arg1 << ", " << quad.arg2 << ", "
                  << quad.result << ")\n";
    }
}

const std::vector<Quadruple> &IntermediateCodeGenerator::getCode() const {
    return code;
}

void IntermediateCodeGenerator::visit(const ASTNode &node) {
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

void IntermediateCodeGenerator::visit(const CompoundStmtNode &node) {
    if (node.first) { visit(*node.first); }
    if (node.second) { visit(*node.second); }
}

void IntermediateCodeGenerator::visit(const IfNode &node) {
    std::string conditionTemp = newTemp();
    visit(*node.condition);
    std::string conditionResult = tempMap[node.condition.get()];

    std::string labelElse = "L" + std::to_string(tempCount++);
    std::string labelEnd = "L" + std::to_string(tempCount++);

    code.emplace_back("ifFalse", conditionResult, "", labelElse);
    visit(*node.thenStmt);
    code.emplace_back("goto", "", "", labelEnd);
    code.emplace_back("label", "", "", labelElse);
    code.emplace_back("label", "", "", labelEnd);
}

void IntermediateCodeGenerator::visit(const IfElseNode &node) {
    std::string conditionTemp = newTemp();
    visit(*node.condition);
    std::string conditionResult = tempMap[node.condition.get()];

    std::string labelElse = "L" + std::to_string(tempCount++);
    std::string labelEnd = "L" + std::to_string(tempCount++);

    code.emplace_back("ifFalse", conditionResult, "", labelElse);
    visit(*node.thenStmt);
    code.emplace_back("goto", "", "", labelEnd);
    code.emplace_back("label", "", "", labelElse);
    visit(*node.elseStmt);
    code.emplace_back("label", "", "", labelEnd);
}

void IntermediateCodeGenerator::visit(const WhileNode &node) {
    std::string labelBegin = "L" + std::to_string(tempCount++);
    std::string labelEnd = "L" + std::to_string(tempCount++);

    code.emplace_back("label", "", "", labelBegin);
    std::string conditionTemp = newTemp();
    visit(*node.condition);
    std::string conditionResult = tempMap[node.condition.get()];

    code.emplace_back("ifFalse", conditionResult, "", labelEnd);
    visit(*node.body);
    code.emplace_back("goto", "", "", labelBegin);
    code.emplace_back("label", "", "", labelEnd);
}

void IntermediateCodeGenerator::visit(const AssignNode &node) {
    visit(*node.value);
    std::string valueResult = tempMap[node.value.get()];
    code.emplace_back("=", valueResult, "", node.id.value);
}

void IntermediateCodeGenerator::visit(const ExprNode &node) {
    visit(*node.left);
    visit(*node.right);

    std::string leftResult = tempMap[node.left.get()];
    std::string rightResult = tempMap[node.right.get()];
    std::string temp = newTemp();

    code.emplace_back(node.op.value, leftResult, rightResult, temp);
    tempMap[&node] = temp;
}

void IntermediateCodeGenerator::visit(const IdentifierNode &node) {
    tempMap[&node] = node.id.value;
}

void IntermediateCodeGenerator::visit(const NumberNode &node) {
    tempMap[&node] = node.value.value;
}

std::string IntermediateCodeGenerator::newTemp() {
    return "t" + std::to_string(tempCount++);
}

} // namespace Compiler
