#pragma once

struct Token {
    enum {
        INT,
        PLUS,
        MINUS,
        MUL,
        DIV,
        MOD,
        EQU
    } type;

    char* val;
};
