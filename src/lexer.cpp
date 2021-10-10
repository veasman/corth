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

    auto GetTokenNum = [=, &input]() mutable -> Token {
        std::string numVal = "";
        while (std::isdigit(m_cCur)) {
            numVal += m_cCur;
            Advance();
            input.get(m_cCur);
        }
        return Token(TokenType_t::NUM, numVal);
    };

    auto GetTokenString = [=, &input]() mutable -> Token {
        std::string opVal = "";
        while (std::isalpha(m_cCur)) {
            opVal += m_cCur;
            Advance();
            input.get(m_cCur);
        }
        std::cout << "Token added. Type: OP, Value: " << opVal << std::endl;
        return Token(TokenType_t::OP, opVal);
    };

    // TODO: This can most likely be faster. I'll worry about it in the future.
    // FIXME: If we can get the current char inside Advance that would make
    //        everything so much easier.
    while (!input.eof()) {
        input.get(m_cCur);

        if (std::isdigit(m_cCur)) {
            m_qTokens.push(GetTokenNum());
        }
        else if (std::isalpha(m_cCur)) { // TODO: Why the hell isnt this working
            m_qTokens.push(GetTokenString());
        }
        else {
            m_qTokens.push(Token(m_cCur));
        }
        Advance();
    }
}
