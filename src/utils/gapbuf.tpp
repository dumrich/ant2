#include "gapbuf.hh"
#include <cstdlib> // access to realloc 
#include <iostream>
#include <cstring>

template <typename T> 
GapBuffer<T>::GapBuffer() {
    buf = (T*)std::calloc(GAP_SIZE, sizeof(T));
    buf_size = GAP_SIZE;
    gap_size = GAP_SIZE;
    gap_start = 0;

    cur_pointer = 0;
}

template <typename T>
void GapBuffer<T>::appendCharacter(T c) {
    if(gap_size == 0) {
        if(expand_gap() == NULL) {
            throw std::runtime_error("Could not increase gap size. `realloc` failed");
        }
    }

    buf[cur_pointer++] = c;
    gap_start++;
    gap_size--;
}

template <typename T>
void GapBuffer<T>::removeCharacter() {
    gap_start--;
    gap_size++;
}

template <typename T>
void GapBuffer<T>::moveCursorLeft() {
    if(cur_pointer == 0) {
        return;
    }

    // swap gap with character
    // TODO: Memcpy and move cursor
    buf[gap_start-- + gap_size] = buf[cur_pointer--];
}

template <typename T>
void GapBuffer<T>::moveCursorRight() {
    if(cur_pointer == buf_size - gap_size) {
        return;
    }

    buf[gap_start] = buf[cur_pointer++ + gap_size];
    gap_start++;
}

template <typename T>
T* GapBuffer<T>::expand_gap() {
    std::cout << "ALERT: Gap Expanding..." << std::endl;
    std::size_t distance_till_end = buf_size - cur_pointer;
    buf_size += GAP_SIZE;
    buf = (T*)std::realloc(buf, buf_size + 2);
    
    // Reflect new gap
    gap_size = GAP_SIZE;

    std::memcpy(buf + buf_size - distance_till_end, buf + cur_pointer, distance_till_end);
    return buf;
}

template <typename T>
void GapBuffer<T>::print_buf(std::ostream& os) {
    for(int i = 0; i < buf_size; i++) {
        if(i == gap_start) {
            i += gap_size - 1;
            continue;
        }
        os << buf[i];
    }
    os << std::endl;
}

template <typename U>
std::ostream& operator<<(std::ostream& os, GapBuffer<U>& obj) {
    obj.print_buf(os);
    return os;
}