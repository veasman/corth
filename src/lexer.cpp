#include <cctype>
#include <fstream>
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
    while (!input.eof()) {
        input.get(m_cCur);
        if (std::isdigit(m_cCur)) {
            m_vTokens.push_back(GetInt());
        }
        else if (m_cCur == '+') {
            m_vTokens.push_back(Token(TokenType_t::ADD));
        }
        else if (m_cCur == '-') {
            m_vTokens.push_back(Token(TokenType_t::SUB));
        }
        else if (m_cCur == '*') {
            m_vTokens.push_back(Token(TokenType_t::MUL));
        }
        else if (m_cCur == '/') {
            m_vTokens.push_back(Token(TokenType_t::DIV));
        }
        else if (m_cCur == '%') {
            m_vTokens.push_back(Token(TokenType_t::MOD));
        }
        else if (m_cCur == '=') {
            m_vTokens.push_back(Token(TokenType_t::EQU));
        }
        Advance();
    }
}

// TODO: Fix this
Token Lexer::GetInt() {
    std::string val;
    while (m_cCur != ' ') {
        val += m_cCur;
    }
    return Token(TokenType_t::INT, val);
}
