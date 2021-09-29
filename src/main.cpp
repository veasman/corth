#include <iostream>
#include <string.h>
#include <vector>
#include "header/lexer.hpp"

int main(int argc, char* argv[]) {
    /*if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            int len = strlen(argv[i]);
            char* fileExt = &argv[i][len - 6];

            // Convert args to string
            //std::vector<std::string> args;
            //args.assign(argv + 1, argv + argc);

            if (strcmp(fileExt, ".corth") == 0) {
                Lexer lexer("") // File here
                lexer.CreateTokens();
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
    }*/

    Lexer lexer("test.corth");
    lexer.CreateTokens();

    for (Token token : lexer.m_vTokens) {
        std::string tokenString;
        switch (token.m_Type) {
        case TokenType_t::INT:
            tokenString = "INT";
            break;
        case TokenType_t::ADD:
            tokenString = "ADD";
            break;
        default:
            tokenString = "OTH";
            break;
        }

        std::cout << tokenString << ", " << token.m_strVal << std::endl;
    }

    return 0;
}
