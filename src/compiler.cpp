#include "CodeGenerator.hpp"
#include "SemanticAnalyzer.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include <fstream>
#include <iostream>
#include <string>

void handle_cmd(const std::string &outputFile);
void handle_file(const char *path, const std::string &outputFile);
void process_code(const std::string &code, const std::string &outputFile);
std::string readInput(const std::string &path);

int main(int argc, char *argv[]) {
    std::string outputFile = "a.out"; // 默认输出文件名

    if (argc <= 1) {
        handle_cmd(outputFile);
    } else if (argc == 2) {
        handle_file(argv[1], outputFile);
    } else if (argc == 4 && std::string(argv[2]) == "-o") {
        outputFile = argv[3];
        handle_file(argv[1], outputFile);
    } else {
        std::cerr << "Usage: " << argv[0] << "( <file_path> [-o <output_file>]\n";
        return 64;
    }

    return 0;
}

void handle_cmd(const std::string &outputFile) {
    std::cout << "\033[38;2;0;255;0m"
              << R"(  __  __   ____     _  ____                      _ _            )" << '\n';
    std::cout << R"( |  \\/  | / __ \  __| |/ ___|___  _ __ ___  _ __ (_) | ___ _ __ )" << '\n';
    std::cout << R"( | |\/| |/ / _` |/ _` | |   / _ \| '_ ` _ \| '_ \| | |/ _ \ '__|)" << '\n';
    std::cout << R"( | |  | | | (_| | (_| | |__| (_) | | | | | | |_) | | |  __/ |   )" << '\n';
    std::cout << R"( |_|  |_|\ \__,_|\__,_|\____\___/|_| |_| |_| .__/|_|_|\___|_|   )" << '\n';
    std::cout << R"(          \____/                           |_|                  )" << '\n';
    std::cout << R"(   >M@dCompiler Designed by xiaojiong liyunfeng wuzhengbang<                       )" << '\n';
    std::string code;
    std::cout << "请输入代码(输入 exit 结束代码输入): \n";
    code = "";
    while (true) {
        std::cout << "ready> ";
        std::string code_tmp;
        std::getline(std::cin, code_tmp);
        if (code_tmp == "exit") { break; }
        code += code_tmp + '\n';
    }
    process_code(code, outputFile);
}

void handle_file(const char *path, const std::string &outputFile) {
    std::string code = readInput(path);
    process_code(code, outputFile);
}

void process_code(const std::string &code, const std::string &outputFile) {
    Compiler::Lexer lexer(code);
    Compiler::Parser parser(lexer);
    auto ast = parser.parse();

    if (ast) {
        std::cout << "语法分析成功!" << '\n';
        ast->print();
        std::cout << '\n';

        Compiler::SemanticAnalyzer analyzer;
        analyzer.analyze(ast);

        Compiler::IntermediateCodeGenerator codeGen;
        codeGen.generate(ast);
        codeGen.print();

        // 保存生成的中间代码到指定文件
        std::ofstream outFile(outputFile);
        if (outFile.is_open()) {
            for (const auto &quad : codeGen.getCode()) {
                outFile << "(" << quad.op << ", " << quad.arg1 << ", " << quad.arg2 << ", "
                        << quad.result << ")\n";
            }
            outFile.close();
            std::cout << "文件已保存到 " << outputFile << '\n';
        } else {
            std::cerr << "错误: 无法打开文件 " << outputFile << '\n';
        }
    } else {
        std::cerr << "解析失败!" << '\n';
    }
}

std::string readInput(const std::string &path) {
    std::ifstream inputFile(path);
    if (!inputFile.is_open()) {
        std::cerr << "Error: unable to open file!" << '\n';
        return "";
    }
    return std::string{
        (std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>()};
}
