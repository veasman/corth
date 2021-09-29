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
    // FIXME: If we can get the current char inside advance that would make
    //        everything so much easier.
    while (!input.eof()) {
        input.get(m_cCur);

        if (std::isdigit(m_cCur)) {
            // TODO: This block is messy, not much I can do about it though
            std::string numVal = "";
            int dots = 0;

            while (std::isdigit(m_cCur) || m_cCur == '.') {
                if (m_cCur == '.' && dots < 1) {
                    dots++;
                    numVal += ".";
                }
                else {
                    numVal += m_cCur;
                }
                Advance();
                input.get(m_cCur);
            }
            m_vTokens.push_back(Token(TokenType_t::NUM, numVal));
        }
        else if (m_cCur != 10) { // Ghetto fix but fine for now
            // If we had an else here, nonesense tokens would be created
            m_vTokens.push_back(Token(m_cCur));
        }
        Advance();
    }
}
