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
    END_OF_FILE = 6,
    UNKNOWN = 7
};

class Token {
  public:
    TokenType type;
    std::string value;
    
    Token() : type(UNKNOWN){};
    Token(TokenType type, std::string value);
    
    void print() const;
    
    static std::string typeToString(TokenType type);
};

} // namespace Compiler

#endif // TOKEN_H
