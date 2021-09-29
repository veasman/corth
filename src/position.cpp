#include "header/position.hpp"

Position::Position(int idx, int ln, int col) {
    m_iIdx = idx;
    m_iLn = ln;
    m_iCol = col;
}

void Position::Advance(char c) {
    m_iIdx++;
    m_iCol++;
    if (c == '\n') {
        m_iLn++;
        m_iCol = 0;
    }
}
