#ifndef TOKEN_H
#define TOKEN_H

enum TokenType {
    INT,
    ADD,
    SUB,
    MUL,
    DIVMOD,
    INTRINSIC
};

enum Intrinsics {
    PRINT,
    DROP,
    IF,
    ELSE,
    END,
    NONE
};

struct Token {
    Token(Intrinsics intrinsic, std::string value = "") {
        m_Type = TokenType::INTRINSIC;
        m_Intrinsic = intrinsic;
        m_strValue = value;
    }
    Token(TokenType type, std::string value = "") {
        m_Type = type;
        m_Intrinsic = Intrinsics::NONE;
        m_strValue = value;
    }
    TokenType m_Type;
    Intrinsics m_Intrinsic;
    std::string m_strValue;
};

#endif
