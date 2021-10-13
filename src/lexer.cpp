#include <iostream>
#include <fstream>
#include <utility>
#include "header/lexer.hpp"

#define ADVANCE i++; this->m_iCol++; this->m_iIdx++; cur = line[i];
#define ERR(msg) std::cout \
                << this->m_strFileName \
                << ":" << this->m_iLine \
                << ":" << this->m_iCol \
                << ": Error: " << msg << std::endl; \
                exit(EXIT_FAILURE);

CLexer::CLexer(std::string file) {
    this->m_strFileName = file;
    this->m_qTokens = {};
    this->m_iLine = 1;
    this->m_iCol = 1;
    this->m_iIdx = 1;
}

std::queue<Token> CLexer::GetFileTokens() {
    std::ifstream in(this->m_strFileName);

    for (std::string line; getline(in, line);) {
        for (int i = 0; i < line.size(); i++) {
            char cur = line[i];

            if (cur == '\n') {
                this->m_iCol = 1;
                this->m_iLine++;
                ADVANCE;
            }
            else if (cur == '\t' || cur == ' ') {
                ADVANCE;
            }
            else if (cur == '/' && line[i+1] == '/') {
                while (i < line.size())
                    ADVANCE;
            }
            else if (std::isdigit(cur)) {
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
                if (word == "print") {
                    intrType = Intrinsics::PRINT;
                }
                else if (word == "drop") {
                    intrType = Intrinsics::DROP;
                }
                else {
                    ERR("Unknown intrinsic \"" << word << "\"");
                }

                this->m_qTokens.push(Token(intrType, word));
            }
            else if (cur == '+') {
                this->m_qTokens.push(Token(TokenType::ADD));
                ADVANCE;
            }
            else if (cur == '-') {
                this->m_qTokens.push(Token(TokenType::SUB));
                ADVANCE;
            }
            else if (cur == '*') {
                this->m_qTokens.push(Token(TokenType::MUL));
                ADVANCE;
            }
            else if (cur == '/') {
                this->m_qTokens.push(Token(TokenType::DIVMOD));
                ADVANCE;
            }

            this->m_iCol++;
            this->m_iIdx++;
        }
    }

    return this->m_qTokens;
}
