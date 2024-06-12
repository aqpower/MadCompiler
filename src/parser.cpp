#include "parser.hpp"

Compiler::Parser::Parser(const std::string &input) : input(input), index(0) {
    nextToken();
}

bool Compiler::Parser::parse() {
    return program() && currentToken == "$";
}

void Compiler::Parser::skipWhitespace() {
    while (index < input.length() && isspace(input[index])) { ++index; }
}

void Compiler::Parser::nextToken() {
    skipWhitespace();
    if (index >= input.length()) {
        currentToken = "$";
        return;
    }

    if (isalpha(input[index])) {
        currentToken = "";
        while (index < input.length() && isalnum(input[index])) {
            currentToken += input[index++];
        }
    } else if (isdigit(input[index])) {
        currentToken = "";
        while (index < input.length() && isdigit(input[index])) {
            currentToken += input[index++];
        }
    } else {
        currentToken = input[index++];
    }
}

bool Compiler::Parser::match(const std::string &expected) {
    if (currentToken == expected) {
        nextToken();
        return true;
    }
    return false;
}

bool Compiler::Parser::isID(const std::string &token) const {
    return !token.empty() && isalpha(token[0]);
}

bool Compiler::Parser::isNUM(const std::string &token) const {
    return !token.empty() && isdigit(token[0]);
}

bool Compiler::Parser::program() {
    return block();
}

bool Compiler::Parser::block() {
    if (match("{")) {
        if (stmts() && match("}")) { return true; }
    }
    return false;
}

bool Compiler::Parser::stmts() {
    if (currentToken == "}" || currentToken == "$") {
        return true; // ε
    }
    return stmt() && stmts();
}

bool Compiler::Parser::stmt() {
    if (isID(currentToken)) {
        if (match(currentToken) && match("=") && expr() && match(";")) { return true; }
    } else if (match("if")) {
        if (match("(") && boolExpr() && match(")") && stmt()) {
            if (match("else")) { return stmt(); }
            return true;
        }
    } else if (match("while")) {
        if (match("(") && boolExpr() && match(")") && stmt()) { return true; }
    } else if (block()) {
        return true;
    }
    return false;
}

bool Compiler::Parser::boolExpr() {
    if (expr()) {
        if (match("<") || match("<=") || match(">") || match(">=")) { return expr(); }
        return true;
    }
    return false;
}

bool Compiler::Parser::expr() {
    if (term()) {
        while (match("+") || match("-")) {
            if (!term()) { return false; }
        }
        return true;
    }
    return false;
}

bool Compiler::Parser::term() {
    if (factor()) {
        while (match("*") || match("/")) {
            if (!factor()) { return false;
}
        }
        return true;
    }
    return false;
}

bool Compiler::Parser::factor() {
    if (match("(")) {
        if (expr() && match(")")) { return true; }
    } else if (isID(currentToken) && match(currentToken)) {
        return true;
    } else if (isNUM(currentToken) && match(currentToken)) {
        return true;
    }
    return false;
}
