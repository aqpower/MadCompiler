#include "parser.hpp"
#include <iostream>

namespace Compiler {

Parser::Parser(Lexer &lexer) : lexer(lexer), currentToken(TokenType::END_OF_FILE, "") {
    advance();
}

void Parser::advance() {
    currentToken = lexer.nextToken();
    // std::cout << "Current token: " << currentToken.value<< " ("
    //   << static_cast<int>(currentToken.type) << ")\n";
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
    if (!result || currentToken.type != TokenType::END_OF_FILE) {
        std::cerr << "语法分析失败: " << currentToken.value << " ("
                  << static_cast<int>(currentToken.type) << ")\n";
        exit(-11);
        return nullptr;
    }
    return result;
}

std::unique_ptr<ASTNode> Parser::program() {
    // std::cout << "Parsing program...\n";
    return block();
}

std::unique_ptr<ASTNode> Parser::block() {
    // std::cout << "Parsing block...\n";
    if (match(Token(TokenType::SEPARATOR, "{"))) {
        // std::cout << "Block found!\n";
        auto stmtsNode = stmts();
        if (match(Token(TokenType::SEPARATOR, "}"))) { return stmtsNode; }
    }
    return nullptr;
}

std::unique_ptr<ASTNode> Parser::stmts() {
    // std::cout << "Parsing stmts...\n";
    // !stmts 为空时返回一个空节点，且当前token为 "}"
    if (currentToken.type == TokenType::SEPARATOR && currentToken.value == "}") {
        return std::make_unique<EmptyNode>();
    }
    auto stmtNode = stmt();
    auto stmtsNode = stmts();
    return std::make_unique<CompoundStmtNode>(std::move(stmtNode), std::move(stmtsNode));
}

std::unique_ptr<ASTNode> Parser::stmt() {
    // std::cout << "Parsing stmt...\n";
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
    // std::cout << "Parsing boolExpr...\n";
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

std::unique_ptr<ASTNode> Parser::expr() {
    // std::cout << "Parsing expr...\n";
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

std::unique_ptr<ASTNode> Parser::term() {
    // std::cout << "Parsing term...\n";
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
    // std::cout << "Parsing factor...\n";
    if (currentToken.type == TokenType::SEPARATOR && currentToken.value == "(") {
        advance();
        auto node = expr();
        if (match(Token(TokenType::SEPARATOR, ")"))) { return node; }
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
