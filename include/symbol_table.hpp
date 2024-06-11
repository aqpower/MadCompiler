#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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

    std::string symbol;
    int tokenType;
};

class SymbolTable {
  public:
    void insertSymbol(const std::string &symbol, int tokenType);
    void printTable();

  private:
    std::vector<SymbolTableEntry> entries;
};

extern SymbolTable symbolTable;
extern const std::unordered_set<std::string> KEYWORDS;
extern const std::unordered_set<std::string> SEPARATORS;
extern std::unordered_map<std::string, TokenType> operatorSeparatorMap;

bool isKeyword(const std::string &word);
bool isSeparator(const std::string &charStr);
void handleAlpha(const std::string &code, size_t &index);
void handleDigit(const std::string &code, size_t &index);
bool handleSeparatorOrOperator(const std::string &code, size_t &index);

#endif // SYMBOL_TABLE_HPP
