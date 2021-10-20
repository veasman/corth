#ifndef LEXER_H
#define LEXER_H

#include <deque>
#include "token.hpp"

class CLexer {
public:
    CLexer(std::string file);
    std::deque<Token> GetFileTokens();

private:
    std::string m_strFileName;
    std::deque<Token> m_qTokens;
    int m_iLine;
    int m_iCol;
    int m_iIdx;
    // TODO: These variables suck, but I can't think of a better way to keep
    //       track of stuff for conditionals.
    int m_iDoAddr;
    int m_iElseAddr;
    int m_iEndAddr;
};

#endif
