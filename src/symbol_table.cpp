#include "symbol_table.hpp"
#include <cctype>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

namespace Compiler {

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

SymbolTableEntry::SymbolTableEntry(int tokenType, const std::string &symbol)
    : symbol(symbol), tokenType(tokenType) {
}

void SymbolTable::insertSymbol(const std::string &symbol, int tokenType) {
    entries.emplace_back(tokenType, symbol);
}

void SymbolTable::printTable() const {
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

void SymbolTable::handleAlpha(const std::string &code, size_t &index) {
    size_t end = index + 1;
    while (end < code.size() && isalnum(code[end])) { end++; }
    std::string word = code.substr(index, end - index);
    index = end - 1;
    insertSymbol(word, isKeyword(word) ? KEYWORD : IDENTIFIER);
}

void SymbolTable::handleDigit(const std::string &code, size_t &index) {
    size_t end = index + 1;
    while (end < code.size() && isdigit(code[end])) { end++; }
    std::string num = code.substr(index, end - index);
    insertSymbol(num, CONSTANT);
    index = end - 1;
}

bool SymbolTable::handleSeparatorOrOperator(
    const std::string &code, size_t &index) {
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
        insertSymbol(currentChar, operatorSeparatorMap[currentChar]);
    } else {
        return false;
    }
    return true;
}

void SymbolTable::analyze(const std::string &code) {
    for (size_t i = 0; i < code.size(); i++) {
        if (isspace(code[i])) { continue; }
        if (isalpha(code[i])) {
            handleAlpha(code, i);
        } else if (isdigit(code[i])) {
            handleDigit(code, i);
        } else {
            if (!handleSeparatorOrOperator(code, i)) {
                std::cerr << "错误： " << code[i] << " 不是有效的操作符！"
                          << '\n';
            }
        }
    }
}

std::string readInput(const std::string &path) {
    std::ifstream inputFile(path);
    if (!inputFile.is_open()) {
        std::cerr << "错误：无法打开文件！" << '\n';
        return "";
    }
    return std::string(
        (std::istreambuf_iterator<char>(inputFile)),
        std::istreambuf_iterator<char>());
}

} // namespace Compiler
