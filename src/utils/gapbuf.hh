#pragma once

#include <cstddef>
#include <iostream>

#define GAP_SIZE 10

template <typename T> class GapBuffer {
private:
    T* buf;
    std::size_t buf_size;
    std::size_t gap_size;
    std::size_t gap_start;

    std::size_t cur_pointer;

    T* expand_gap();
public:
    GapBuffer();

    // Core Actions
    void appendCharacter(T c);
    void moveCursorLeft();
    void moveCursorRight();

    void removeCharacter();

    // Override <<
    void print_buf(std::ostream& os);

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const GapBuffer<char>& obj);
};

#include "gapbuf.tpp"