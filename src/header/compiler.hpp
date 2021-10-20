#ifndef COMPILER_H
#define COMPILER_H

#include <deque>
#include "token.hpp"

class CComplier {
public:
    CComplier(std::string fileName, std::deque<Token> tokens);
    void GenerateNasm();
    void CompileNasm();

private:
    std::string m_strFileName;
    std::deque<Token> m_qTokens;
};

#endif
