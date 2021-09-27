#pragma once
#include <iostream>

class Position {
public:
    int ln;
    int col;

    void advance(std::string c) {
        col++;
        if (c == "\n") {
            ln++;
            col = 0;
        }
    }
};
