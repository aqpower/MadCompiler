#include "lexer.hpp"
#include "parser.hpp"
#include <iostream>

void handle_cmd();
void handle_file(const char *path);

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        handle_cmd();
    } else if (argc == 2) {
        handle_file(argv[1]);
    } else {
        std::cerr << "用法: " << argv[0] << " <文件路径>" << '\n';
        perror("Usage: toy.out [path]");
        return 64;
    }

    return 0;
}

void handle_cmd() {
    std::string code;
    Compiler::SymbolTable symbolTable;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, code);
        symbolTable.analyze(code);
        std::cout << "your input: " << code << '\n';
    }
    symbolTable.printTable();
}

void handle_file(const char *path) {
    std::string code = Compiler::readInput(path);
    if (code.empty()) { return; }
    Compiler::SymbolTable symbolTable;
    symbolTable.analyze(code);
    symbolTable.printTable();

    std::string input = "{ id = id + num ; }";
    Parser parser(input);
    if (parser.parse()) {
        std::cout << "Parsing successful!" << '\n';
    } else {
        std::cerr << "Parsing failed!" << '\n';
    }
}
