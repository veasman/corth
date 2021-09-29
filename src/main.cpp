#include <iostream>
#include <string.h>
#include <vector>
#include "header/lexer.hpp"

int main(int argc, char* argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            int len = strlen(argv[i]);
            char* fileExt = &argv[i][len - 6];

            if (strcmp(fileExt, ".corth") == 0) {
                Lexer lexer(argv[i]);
                lexer.CreateTokens();

                // Corth will do more later, but for now it will just show you
                // the tokens created from a given file
                for (Token token : lexer.m_vTokens) {
                    std::string tokenString;
                    switch (token.m_Type) {
                    case TokenType_t::NUM:
                        tokenString = "NUM";
                        break;
                    case TokenType_t::FLT:
                        tokenString = "FLT";
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
                    default:
                        tokenString = "OTH";
                        break;
                    }
                    std::cout <<
                        "[" << tokenString <<
                        ", " << token.m_strVal <<
                        "]" << std::endl;
                }
            }
            else {
                std::cout << "Error: File must end in \".corth\"" << std::endl;
            }
        }
    }
    else {
        // Maybe live interpreter later?
        std::cout << "Error: Please provide a file" << std::endl;
        return 1;
    }

    return 0;
}
