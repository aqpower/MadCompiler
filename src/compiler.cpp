#include "lexer.hpp"
#include "parser.hpp"
#include <fstream>
#include <iostream>
#include <string>

void handle_cmd();
void handle_file(const char *path);
std::string readInput(const std::string &path);

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
    std::cout << "Enter 'exit' to quit." << '\n';
    code = "";
    while (true) {
        std::cout << "ready> ";
        std::string code_tmp;
        std::getline(std::cin, code_tmp);
        if (code_tmp == "exit") { break; }
        code += code_tmp + '\n';
    }
    Compiler::Lexer lexer(code);
    Compiler::Parser parser(lexer);
    auto ast = parser.parse();
    
    if (ast) {
        std:: cout << "Parsing successful!" << '\n';
        ast->print();
        std::cout << '\n';
    } else {
        std::cerr << "Parsing failed!" << '\n';
    }
}

void handle_file(const char *path) {
    std::string code = readInput(path);

    Compiler::Lexer lexer(code);

    Compiler::Parser parser(lexer);
    auto ast = parser.parse();
    
    if (ast) {
        ast->print();
        std::cout << '\n';
    } else {
        std::cerr << "Parsing failed!" << '\n';
    }
}

std::string readInput(const std::string &path) {
    std::ifstream inputFile(path);
    if (!inputFile.is_open()) {
        std::cerr << "错误：无法打开文件！" << '\n';
        return "";
    }
    return std::string{
        (std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>()};
}
