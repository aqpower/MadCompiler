#include "token.hpp"
#include <iostream>
#include <utility>

namespace Compiler {

Token::Token(TokenType type, std::string value) : type(type), value(std::move(value)) {
}

void Token::print() const {
    std::cout << "Token: " << value << " (" << typeToString(type) << ")\n";
}

std::string Token::typeToString(TokenType type) {
    switch (type) {
        case TokenType::KEYWORD:
            return "KEYWORD";
        case TokenType::IDENTIFIER:
            return "IDENTIFIER";
        case TokenType::CONSTANT:
            return "CONSTANT";
        case TokenType::OPERATOR:
            return "OPERATOR";
        case TokenType::SEPARATOR:
            return "SEPARATOR";
        case TokenType::END_OF_FILE:
            return "END_OF_FILE";
        default:
            return "UNKNOWN";
    }
}

} // namespace Compiler
