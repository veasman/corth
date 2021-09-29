#pragma once
#include <vector>
#include "position.hpp"
#include "token.hpp"

class Lexer {
public:
    std::string m_strFile;
    Position m_Pos = Position(-1, 0, -1); // Why do I need to initialize here?
    std::vector<Token> m_vTokens; // TODO: Maybe this could be a queue (fifo)
    char m_cCur;

    Lexer(std::string file);
    void Advance();
    void CreateTokens();
};
