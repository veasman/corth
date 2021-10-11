#ifndef COMPILER_H
#define COMPILER_H

#include <queue>
#include "token.hpp"

class CComplier {
public:
    CComplier(std::string fileName, std::queue<Token> tokens);
    void NasmCompile();

private:
    std::string m_strFileName;
    std::queue<Token> m_qTokens;
};

#endif
