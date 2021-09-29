#pragma once
#include <iostream>

class Position {
public:
    int m_iIdx;
    int m_iLn;
    int m_iCol;

    Position(int idx, int ln, int col);
    void Advance(char c);
};
