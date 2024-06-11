#include "lexer.hpp"
#include "symbol_table.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << '\n';
        return 1;
    }

    std::string code = readInput(argv[1]);
    if (code.empty()) { return 1; }

    analyze(code);
    symbolTable.printTable();

    return 0;
}
