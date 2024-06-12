#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace Compiler {

class Lexer {
  public:
    explicit Lexer(std::string code);
    Token nextToken();

  private:
    std::string code;
    size_t index;

    const std::unordered_set<std::string> KEYWORDS = {"if",   "int",    "while", "do",
                                                      "else", "return", "break", "continue"};

    const std::unordered_set<std::string> SEPARATORS = {",", ";", "(", ")", "{", "}"};
    std::unordered_map<std::string, TokenType> operatorSeparatorMap = {
        {"+", OPERATOR},  {"-", OPERATOR},  {"*", OPERATOR},  {"/", OPERATOR},
        {"=", OPERATOR},  {"!=", OPERATOR}, {"<", OPERATOR},  {"<=", OPERATOR},
        {">", OPERATOR},  {">=", OPERATOR},

        {",", SEPARATOR}, {";", SEPARATOR}, {"(", SEPARATOR}, {")", SEPARATOR},
        {"{", SEPARATOR}, {"}", SEPARATOR}};
    void skipWhitespace();
    Token handleAlpha();
    Token handleDigit();
    Token handleSeparatorOrOperator();
    bool isKeyword(const std::string &);
    bool isSeparator(const std::string &);
};

} // namespace Compiler

#endif // LEXER_HPP
