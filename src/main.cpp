#include <iostream>
#include <string.h>
#include <queue>
#include "header/lexer.hpp"

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

        Lexer lexer(argv[i]);
        lexer.CreateTokens();

        // Corth will do more later, but for now it will just show you
        // the tokens created from a given file
        for (int i = 0; i < lexer.m_qTokens.size(); i++) {
            Token token = lexer.m_qTokens.front();
            std::string tokenString;
            switch (token.m_Type) {
            case TokenType_t::NUM:
                tokenString = "NUM: " + token.m_strVal;
                break;
            case TokenType_t::ADD:
                tokenString = "ADD";
                break;
            case TokenType_t::SUB:
                tokenString = "SUB";
                break;
            case TokenType_t::MUL:
                tokenString = "MUL";
                break;
            case TokenType_t::DIV:
                tokenString = "DIV";
                break;
            case TokenType_t::MOD:
                tokenString = "MOD";
                break;
            case TokenType_t::EQU:
                tokenString = "EQU";
                break;
            case TokenType_t::OP:
                tokenString = "OP: " + token.m_strVal;
                break;
            default:
                tokenString = "OTH";
                break;
            }
            std::cout << "[" << tokenString << "]" << std::endl;
            lexer.m_qTokens.pop();
        }
    }

    return 0;
}
