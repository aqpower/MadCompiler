#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace Compiler {

enum TokenType {
    KEYWORD = 1,
    IDENTIFIER = 2,
    CONSTANT = 3,
    OPERATOR = 4,
    SEPARATOR = 5,
    END_OF_FILE = 6
};

class Token {
  public:
    Token(TokenType type, const std::string &value);
    TokenType type;
    std::string value;
    void print() const;
    static std::string typeToString(TokenType type);
};

} // namespace Compiler

#endif // TOKEN_H
