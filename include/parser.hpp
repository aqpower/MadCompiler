#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>

namespace Compiler {

class Parser {
  public:
    explicit Parser(const std::string &input);
    bool parse();

  private:
    std::string input;
    size_t index;
    std::string currentToken;

    bool program();
    bool block();
    bool stmts();
    bool stmt();
    bool boolExpr();
    bool expr();
    bool term();
    bool factor();

    void skipWhitespace();
    void nextToken();
    bool match(const std::string &expected);
    bool isID(const std::string &token) const;
    bool isNUM(const std::string &token) const;
};

} // namespace Compiler

#endif // PARSER_HPP
