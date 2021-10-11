#ifndef TOKEN_H
#define TOKEN_H

enum TokenType {
    INT,
    PLUS,
    WORD
};

struct Token {
    Token(TokenType type, std::string value) {
        m_Type = type;
        m_strValue = value;
    }
    TokenType m_Type;
    std::string m_strValue;
};

#endif
