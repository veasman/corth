#pragma once
#include <iostream>

enum TokenType_t {
    INT,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    EQU
};

struct Token {
    Token(TokenType_t type, std::string val = "") {
        m_Type = type;
        m_strVal = val;
    }
    TokenType_t m_Type;
    std::string m_strVal;
};
