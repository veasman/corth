#include <iostream>
#include <fstream>
#include <utility>
#include "header/lexer.hpp"

#define ADVANCE i++; this->m_iCol++; this->m_iIdx++; cur = line[i];
#define ERR(msg) std::cout \
                << this->m_strFileName \
                << ":" << this->m_iLine \
                << ":" << this->m_iCol - word.length() \
                << ": Error: " << msg << std::endl; \
                exit(EXIT_FAILURE);

CLexer::CLexer(std::string file) {
    this->m_strFileName = file;
    this->m_qTokens = {};
    this->m_iLine = 1;
    this->m_iCol = 1;
    this->m_iIdx = 1;
}

std::deque<Token> CLexer::GetFileTokens() {
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
                while (i < line.size()) {
                    ADVANCE;
                }
            }
            else if (std::isdigit(cur)) {
                std::string number = "";
                while (std::isdigit(cur)) {
                    number += cur;
                    ADVANCE;
                }
                this->m_qTokens.push_back(Token(TokenType::INT, number));
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
                else if (word == "dup") {
                    intrType = Intrinsics::DUP;
                }
                else if (word == "if") {
                    intrType = Intrinsics::IF;
                }
                else if (word == "while") {
                    intrType = Intrinsics::WHILE;
                }
                else if (word == "do") {
                    intrType = Intrinsics::DO;
                    this->m_iDoAddr = this->m_qTokens.size();
                }
                else if (word == "else") {
                    intrType = Intrinsics::ELSE;
                    this->m_iElseAddr = this->m_qTokens.size();
                    this->m_qTokens[this->m_iDoAddr].m_iConPair = this->m_qTokens.size() + 1;
                }
                else if (word == "end") {
                    intrType = Intrinsics::END;
                    this->m_iEndAddr = this->m_qTokens.size();
                    this->m_qTokens[this->m_iElseAddr].m_iConPair = this->m_qTokens.size();
                }
                else {
                    ERR("Unknown word \"" << word << "\"");
                }

                this->m_qTokens.push_back(Token(intrType, word));
            }
            // This is hard to look at. Might fix in the future.
            else if (cur == '+') {
                this->m_qTokens.push_back(Token(TokenType::ADD));
                ADVANCE;
            }
            else if (cur == '-') {
                this->m_qTokens.push_back(Token(TokenType::SUB));
                ADVANCE;
            }
            else if (cur == '*') {
                this->m_qTokens.push_back(Token(TokenType::MUL));
                ADVANCE;
            }
            else if (cur == '/') {
                this->m_qTokens.push_back(Token(TokenType::DIVMOD));
                ADVANCE;
            }
            else if (cur == '=') {
                this->m_qTokens.push_back(Token(Intrinsics::EQ));
                ADVANCE;
            }
            else if (cur == '<') {
                this->m_qTokens.push_back(Token(Intrinsics::LT));
                ADVANCE;
            }
            else if (cur == '>') {
                this->m_qTokens.push_back(Token(Intrinsics::GT));
                ADVANCE;
            }
            else if (cur == '!' && line[i+1] == '=') {
                this->m_qTokens.push_back(Token(Intrinsics::NE));
                ADVANCE;
                ADVANCE;
            }

            this->m_iCol++;
            this->m_iIdx++;
        }
    }

    return this->m_qTokens;
}
