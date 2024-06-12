#include "lexer.hpp"
#include <cctype>
#include <unordered_set>

namespace Compiler {

Lexer::Lexer(std::string code) : code(std::move(code)), index(0) {
}

void Lexer::skipWhitespace() {
    while (index < code.length() && isspace(code[index])) { ++index; }
}

Token Lexer::nextToken() {
    skipWhitespace();
    if (index >= code.length()) { return Token{TokenType::END_OF_FILE, ""}; }

    char currentChar = code[index];

    if (isalpha(currentChar)) { return handleAlpha(); }
    if (isdigit(currentChar)) { return handleDigit(); }
    return handleSeparatorOrOperator();
    // return Token(TokenType::END_OF_FILE, ""); // Unrecognized character
}

Token Lexer::handleAlpha() {
    std::string value;
    while (index < code.length() && isalnum(code[index])) {
        value += code[index];
        ++index;
    }

    return isKeyword(value) ? Token{TokenType::KEYWORD, value}
                            : Token{TokenType::IDENTIFIER, value};
}

Token Lexer::handleDigit() {
    std::string value;
    while (index < code.length() && isdigit(code[index])) { value += code[index++]; }
    return Token{TokenType::CONSTANT, value};
}

Token Lexer::handleSeparatorOrOperator() {
    std::string currentWord(&code[index], 1);

    if (currentWord == "<" || currentWord == ">" || currentWord == "!") {
        if (index + 1 < code.size()) {
            std::string nextChar(&code[index + 1], 1);
            std::string combined = currentWord + nextChar;
            if (operatorSeparatorMap.find(combined) != operatorSeparatorMap.end()) {
                currentWord = combined;
                index++;
            }
        }
    }
    index++;
    if (operatorSeparatorMap.find(currentWord) != operatorSeparatorMap.end()) {
        return Token{operatorSeparatorMap[currentWord], currentWord};
    }
    return Token{TokenType::END_OF_FILE, ""}; // Unrecognized character
}

bool Lexer::isKeyword(const std::string &word) {
    return KEYWORDS.find(word) != KEYWORDS.end();
}

bool Lexer::isSeparator(const std::string &word) {
    return SEPARATORS.find(word) != SEPARATORS.end();
}

} // namespace Compiler
