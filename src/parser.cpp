#include "parser.hpp"
#include "token.hpp"
#include <iostream>

namespace Compiler {

Parser::Parser(Lexer &lexer) : lexer(lexer), currentToken(TokenType::END_OF_FILE, "") {
    advance();
}

void Parser::advance() {
    currentToken = lexer.nextToken();
    std::cout << "Current token: " << currentToken.value << " ("
              << static_cast<int>(currentToken.type) << ")\n"; // 输出调试信息
}

bool Parser::match(const Token &token) {
    if (currentToken.type == token.type && currentToken.value == token.value) {
        advance();
        return true;
    }
    return false;
}

bool Parser::match(TokenType type) {
    if (currentToken.type == type) {
        advance();
        return true;
    }
    return false;
}

bool Parser::match(const std::string &value) {
    if (currentToken.value == value) {
        advance();
        return true;
    }
    return false;
}

std::unique_ptr<ASTNode> Parser::parse() {
    auto result = program();
    if (!result) {
        std::cerr << "Parsing failed at token: " << currentToken.value << " ("
                  << static_cast<int>(currentToken.type) << ")\n";
    }
    return result;
}

std::unique_ptr<ASTNode> Parser::program() {
    std::cout << "Parsing program...\n";
    return block();
}

// std::unique_ptr<ASTNode> Parser::block() {
//     std::cout << "Parsing block...\n";
//     // !error 你的currenttoken match之后都被改变啦！
//     if (match(TokenType::SEPARATOR) && currentToken.value == "{") {
//         std::cout << "Block found!\n";
//         auto stmtsNode = stmts();
//         if (match(TokenType::SEPARATOR) && currentToken.value == "}") { return stmtsNode; }
//     }
//     return nullptr;
// }

std::unique_ptr<ASTNode> Parser::block() {
    std::cout << "Parsing block...\n";
    if (match(Token(TokenType::SEPARATOR, "{"))) {
        std::cout << "Block found!\n";
        auto stmtsNode = stmts();
        if (match(Token(TokenType::SEPARATOR, "}"))) { return stmtsNode; }
    }
    return nullptr;
}

// stmts means statements
std::unique_ptr<ASTNode> Parser::stmts() {
    std::cout << "Parsing stmts...\n";
    if (match(Token(TokenType::SEPARATOR, "}"))) {
        return std::make_unique<EmptyNode>(); // 使用 EmptyNode 表示空节点
    }
    auto stmtNode = stmt();
    auto stmtsNode = stmts();
    return std::make_unique<CompoundStmtNode>(std::move(stmtNode), std::move(stmtsNode));
}

// stmt means statement 语句
std::unique_ptr<ASTNode> Parser::stmt() {
    std::cout << "Parsing stmt...\n"; // 输出调试信息
    if (currentToken.type == TokenType::IDENTIFIER) {
        auto idToken = currentToken;
        advance();
        if (match(Token(TokenType::OPERATOR, "="))) {
            auto exprNode = expr();
            if (match(Token(TokenType::SEPARATOR, ";"))) {
                return std::make_unique<AssignNode>(idToken, std::move(exprNode));
            }
        }
    } else if (match(Token(TokenType::KEYWORD, "if"))) {
        if (match(Token(TokenType::SEPARATOR, "("))) {
            auto boolNode = boolExpr();
            if (match(Token(TokenType::SEPARATOR, ")"))) {
                auto stmtNode = stmt();
                if (match(Token(TokenType::KEYWORD, "else"))) {
                    auto elseNode = stmt();
                    return std::make_unique<IfElseNode>(
                        std::move(boolNode), std::move(stmtNode), std::move(elseNode));
                }
                return std::make_unique<IfNode>(std::move(boolNode), std::move(stmtNode));
            }
        }
    } else if (match(Token(TokenType::KEYWORD, "while"))) {
        if (match(Token(TokenType::SEPARATOR, "("))) {
            auto boolNode = boolExpr();
            if (match(Token(TokenType::SEPARATOR, ")"))) {
                auto stmtNode = stmt();
                return std::make_unique<WhileNode>(std::move(boolNode), std::move(stmtNode));
            }
        }
    } else if (currentToken.type == TokenType::SEPARATOR && currentToken.value == "{") {
        return block();
    }
    return nullptr;
}

std::unique_ptr<ASTNode> Parser::boolExpr() {
    std::cout << "Parsing boolExpr...\n"; // 输出调试信息
    auto left = expr();
    if (currentToken.type == TokenType::OPERATOR
        && (currentToken.value == "<" || currentToken.value == "<=" || currentToken.value == ">"
            || currentToken.value == ">=")) {
        Token op = currentToken;
        advance();
        auto right = expr();
        return std::make_unique<ExprNode>(std::move(left), op, std::move(right));
    }
    return left;
}

// expr means 表达式
std::unique_ptr<ASTNode> Parser::expr() {
    std::cout << "Parsing expr...\n"; // 输出调试信息
    auto left = term();
    while (currentToken.type == TokenType::OPERATOR
           && (currentToken.value == "+" || currentToken.value == "-")) {
        Token op = currentToken;
        advance();
        auto right = term();
        left = std::make_unique<ExprNode>(std::move(left), op, std::move(right));
    }
    return left;
}

// term means 项
std::unique_ptr<ASTNode> Parser::term() {
    std::cout << "Parsing term...\n"; // 输出调试信息
    auto left = factor();
    while (currentToken.type == TokenType::OPERATOR
           && (currentToken.value == "*" || currentToken.value == "/")) {
        Token op = currentToken;
        advance();
        auto right = factor();
        left = std::make_unique<ExprNode>(std::move(left), op, std::move(right));
    }
    return left;
}

std::unique_ptr<ASTNode> Parser::factor() {
    std::cout << "Parsing factor...\n"; // 输出调试信息
    if (currentToken.type == TokenType::SEPARATOR && currentToken.value == "(") {
        auto node = expr();
        if (currentToken.type == TokenType::SEPARATOR && currentToken.value == ")") { return node; }
    } else if (currentToken.type == TokenType::IDENTIFIER) {
        Token idToken = currentToken;
        advance();
        return std::make_unique<IdentifierNode>(idToken);
    } else if (currentToken.type == TokenType::CONSTANT) {
        Token numToken = currentToken;
        advance();
        return std::make_unique<NumberNode>(numToken);
    }
    return nullptr;
}

} // namespace Compiler
