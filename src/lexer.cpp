#include <iostream>
#include <cctype>
#include <fstream>
#include <queue>
#include "header/lexer.hpp"

Lexer::Lexer(std::string file) {
    m_strFile = file;
    m_Pos = Position(-1, 0, -1);
    Advance();
}

void Lexer::Advance() {
    m_Pos.Advance(m_cCur);
}

void Lexer::CreateTokens() {
    std::ifstream input(m_strFile);

    // TODO: This can most likely be faster. I'll worry about it in the future.
    // FIXME: If we can get the current char inside advance that would make
    //        everything so much easier.
    while (!input.eof()) {
        input.get(m_cCur);

        if (std::isdigit(m_cCur)) {
            // TODO: This block is messy, not much I can do about it though
            std::string numVal = "";
            while (std::isdigit(m_cCur)) {
                numVal += m_cCur;
                Advance();
                input.get(m_cCur);
            }
            m_qTokens.push(Token(TokenType_t::NUM, numVal));
        }
        else if (std::isalpha(m_cCur)) { // TODO: Why the hell isnt this working
            std::string opVal = "";
            while (std::isalpha(m_cCur)) {
                opVal += m_cCur;
                Advance();
                input.get(m_cCur);
            }
            std::cout << opVal << std::endl;
            m_qTokens.push(Token(TokenType_t::OP, opVal));
        }
        else {
            m_qTokens.push(Token(m_cCur));
        }
        Advance();
    }
}
