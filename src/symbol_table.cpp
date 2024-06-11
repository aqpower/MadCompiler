#include "symbol_table.hpp"
#include <iostream>

const std::unordered_set<std::string> KEYWORDS = {
    "if", "int", "for", "while", "do", "return", "break", "continue"};

const std::unordered_set<std::string> SEPARATORS = {",", ";", "(",
                                                    ")", "{", "}"};

std::unordered_map<std::string, TokenType> operatorSeparatorMap = {
    {"+", OPERATOR},  {"-", OPERATOR},  {"*", OPERATOR},  {"/", OPERATOR},
    {"=", OPERATOR},  {":=", OPERATOR}, {"<", OPERATOR},  {"<=", OPERATOR},
    {">", OPERATOR},  {">=", OPERATOR}, {"<>", OPERATOR}, {",", SEPARATOR},
    {";", SEPARATOR}, {"(", SEPARATOR}, {")", SEPARATOR}, {"{", SEPARATOR},
    {"}", SEPARATOR}};

SymbolTable symbolTable;

SymbolTableEntry::SymbolTableEntry(int tokenType, const std::string &symbol)
    : symbol(symbol), tokenType(tokenType) {
}

void SymbolTable::insertSymbol(const std::string &symbol, int tokenType) {
    entries.emplace_back(tokenType, symbol);
}

void SymbolTable::printTable() {
    for (const auto &entry : entries) {
        std::cout << "(" << entry.tokenType << ", \"" << entry.symbol
                  << "\")\n";
    }
}

bool isKeyword(const std::string &word) {
    return KEYWORDS.find(word) != KEYWORDS.end();
}

bool isSeparator(const std::string &charStr) {
    return SEPARATORS.find(charStr) != SEPARATORS.end();
}

void handleAlpha(const std::string &code, size_t &index) {
    size_t end = index + 1;
    while (end < code.size() && isalnum(code[end])) { end++; }
    std::string word = code.substr(index, end - index);
    index = end - 1;
    symbolTable.insertSymbol(word, isKeyword(word) ? KEYWORD : IDENTIFIER);
}

void handleDigit(const std::string &code, size_t &index) {
    size_t end = index + 1;
    while (end < code.size() && isdigit(code[end])) { end++; }
    std::string num = code.substr(index, end - index);
    symbolTable.insertSymbol(num, CONSTANT);
    index = end - 1;
}

bool handleSeparatorOrOperator(const std::string &code, size_t &index) {
    std::string currentChar(&code[index], 1);

    if (currentChar == "<" || currentChar == ">" || currentChar == ":") {
        if (index + 1 < code.size()) {
            std::string nextChar(&code[index + 1], 1);
            std::string combined = currentChar + nextChar;
            if (operatorSeparatorMap.find(combined)
                != operatorSeparatorMap.end()) {
                currentChar = combined;
                index++;
            }
        }
    }

    if (operatorSeparatorMap.find(currentChar) != operatorSeparatorMap.end()) {
        symbolTable.insertSymbol(
            currentChar, operatorSeparatorMap[currentChar]);
    } else {
        return false;
    }
    return true;
}
