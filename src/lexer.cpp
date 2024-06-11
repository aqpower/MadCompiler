#include "lexer.hpp"
#include "symbol_table.hpp"
#include <cctype>
#include <fstream>
#include <iostream>

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

void analyze(const std::string &code) {
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
