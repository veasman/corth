#pragma once
#include <vector>
#include "position.hpp"
#include "token.hpp"

class Lexer {
public:
    std::string m_strFile;
    Position m_Pos = Position(-1, 0, -1); // Why do I need to initialize here too?
    char m_cCur;
    std::vector<Token> m_vTokens;

    Lexer(std::string file);
    void Advance();
    void CreateTokens();
    Token GetInt();
};
