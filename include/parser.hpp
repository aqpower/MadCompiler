#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"
#include "ast.hpp"

namespace Compiler {

class Parser {
  public:
    explicit Parser(Lexer &lexer);

    std::unique_ptr<ASTNode> parse();

  private:
    Lexer &lexer;
    Token currentToken;

    void advance();
    bool match(const Token &token);
    bool match(TokenType type);
    bool match(const std::string &value);

    std::unique_ptr<ASTNode> program();
    std::unique_ptr<ASTNode> block();
    std::unique_ptr<ASTNode> stmts();
    std::unique_ptr<ASTNode> stmt();
    std::unique_ptr<ASTNode> boolExpr();
    std::unique_ptr<ASTNode> expr();
    std::unique_ptr<ASTNode> term();
    std::unique_ptr<ASTNode> factor();
};

} // namespace Compiler

#endif // PARSER_HPP
