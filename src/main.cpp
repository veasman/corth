#include <iostream>
#include <string.h>
#include "header/lexer.hpp"
#include "header/compiler.hpp"

void PrintUsage() {
    std::cout << "usage: ./corth file.corth" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        PrintUsage();
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        int len = strlen(argv[i]);
        char* fileExt = &argv[i][len - 6];

        if (strcmp(fileExt, ".corth") != 0) {
            PrintUsage();
            return 1;
        }

        CLexer lexer(argv[i]);
        CComplier compiler(argv[i], lexer.GetFileTokens());
        compiler.NasmCompile();
    }

    return 0;
}
