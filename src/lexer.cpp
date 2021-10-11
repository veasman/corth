#include <iostream>
#include <utility>
#include "header/lexer.hpp"

#define ADVANCE i++; this->m_iCol++; this->m_iIdx++; cur = test[i];

CLexer::CLexer(std::string file) {
    this->m_strFileName = file;
    this->m_qTokens = {};
    this->m_iLine = 0;
    this->m_iCol = 0;
    this->m_iIdx = 0;
}

std::queue<Token> CLexer::GetFileTokens() {
    std::string test = "34 35 + print";

    for (int i = 0; i < test.size(); i++) {
        char cur = test[i];

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
            this->m_qTokens.push(Token(TokenType::WORD, word));
        }
        else if (cur == '+') {
            this->m_qTokens.push(Token(TokenType::PLUS, ""));
            ADVANCE;
        }

        this->m_iCol++;
        this->m_iIdx++;
    }

    while (!this->m_qTokens.empty()) {
        std::string output = "";
        switch (this->m_qTokens.front().m_Type) {
        case TokenType::INT:
            output = "INT: " + this->m_qTokens.front().m_strValue;
            break;
        case TokenType::PLUS:
            output = "PLUS";
            break;
        case TokenType::WORD:
            output = "WORD: " + this->m_qTokens.front().m_strValue;
            break;
        }
        this->m_qTokens.pop();

        std::cout << "[" << output << "]" << std::endl;
    }

    return this->m_qTokens;
}
