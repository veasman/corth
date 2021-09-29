#pragma once
#include <iostream>
#include <unordered_map>

enum TokenType_t {
    NUM,
    FLT,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    EQU
};

// Having this map makes it quicker to create tokens, and cleans up the code
inline std::unordered_map<char, TokenType_t> mTokenMap = {
    { '+', TokenType_t::ADD },
    { '-', TokenType_t::SUB },
    { '*', TokenType_t::MUL },
    { '/', TokenType_t::DIV },
    { '%', TokenType_t::MOD },
    { '=', TokenType_t::EQU },
};

struct Token {
    // Access token types based on the char associate with it
    Token(char tokenVal, std::string val = "") {
        m_Type = mTokenMap[tokenVal];
        m_strVal = val;
    }
    TokenType_t m_Type;
    std::string m_strVal;
};
