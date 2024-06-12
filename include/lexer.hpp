#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <string>
#include <vector>

namespace Compiler {

enum TokenType {
    KEYWORD = 1,
    IDENTIFIER = 2,
    CONSTANT = 3,
    OPERATOR = 4,
    SEPARATOR = 5,
};

class SymbolTableEntry {
  public:
    SymbolTableEntry(int tokenType, const std::string &symbol);

    std::string symbol; /**< 符号字符串 */
    int tokenType;      /**< 标记类型 */
};

class SymbolTable {
  public:
    void insertSymbol(const std::string &symbol, int tokenType);
    void printTable() const;
    void analyze(const std::string &code);

  private:
    void handleAlpha(const std::string &code, size_t &index);
    void handleDigit(const std::string &code, size_t &index);
    bool handleSeparatorOrOperator(const std::string &code, size_t &index);

    std::vector<SymbolTableEntry> entries;
};

bool isKeyword(const std::string &word);
bool isSeparator(const std::string &charStr);

std::string readInput(const std::string &path);

} // namespace Compiler

#endif // SYMBOL_TABLE_HPP
