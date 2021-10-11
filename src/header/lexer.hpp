#ifndef LEXER_H
#define LEXER_H

#include <queue>
#include "token.hpp"

class CLexer {
public:
    CLexer(std::string file);
    std::queue<Token> GetFileTokens();

private:
    std::string m_strFileName;
    std::queue<Token> m_qTokens;
    int m_iLine;
    int m_iCol;
    int m_iIdx;
};

#endif
