#include <iostream>
#include <fstream>
#include <utility>
#include "header/lexer.hpp"

#define ADVANCE i++; this->m_iCol++; this->m_iIdx++; cur = line[i];

CLexer::CLexer(std::string file) {
    this->m_strFileName = file;
    this->m_qTokens = {};
    this->m_iLine = 0;
    this->m_iCol = 0;
    this->m_iIdx = 0;
}

std::queue<Token> CLexer::GetFileTokens() {
    std::ifstream in(this->m_strFileName);

    for (std::string line; getline(in, line);) {
        for (int i = 0; i < line.size(); i++) {
            char cur = line[i];

            if (cur == '\n') {
                this->m_iCol = 0;
                this->m_iLine++;
                ADVANCE;
            }

            if (cur == '\t' || cur == ' ') {
                ADVANCE;
            }

            if (std::isdigit(cur)) {
                std::string number = "";
                while (std::isdigit(cur)) {
                    number += cur;
                    ADVANCE;
                }
                this->m_qTokens.push(Token(TokenType::INT, number));
            }
            else if (std::isalpha(cur)) {
                std::string word = "";
                while (std::isalpha(cur)) {
                    word += cur;
                    ADVANCE;
                }
                Intrinsics intrType;
                if (word == "print") intrType = Intrinsics::PRINT;

                this->m_qTokens.push(Token(intrType, word));
            }
            else if (cur == '+') {
                this->m_qTokens.push(Token(TokenType::PLUS, ""));
                ADVANCE;
            }

            this->m_iCol++;
            this->m_iIdx++;
        }
    }

    // Keeping this for debugging later
    /*std::queue<Token> copy = this->m_qTokens;
    while (!copy.empty()) {
        std::string output = "";
        switch (copy.front().m_Type) {
        case TokenType::INT:
            output = "INT: " + copy.front().m_strValue;
            break;
        case TokenType::PLUS:
            output = "PLUS";
            break;
        case TokenType::INTRINSIC:
            output = "INTRINSIC: " + copy.front().m_strValue;
            break;
        }
        copy.pop();

        std::cout << "[" << output << "]" << std::endl;
    }*/

    return this->m_qTokens;
}
