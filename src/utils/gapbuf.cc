#include "gapbuf.hh"
#include <cstdlib>
#include <cstring>
#include <cmath>

Membuf::Membuf(char* b, size_t l, size_t gap) : buf_len(l), buf(b), cursor(0), gap(gap) {}

int Membuf::insert(char new_char) {
    if(gap > 0) {
        buf[cursor++] = new_char;
        buf_len++;
        gap--;
        return 0;
    }

    // Reallocate Buffer
    char* new_buf = (char*)malloc(buf_len);

    // Copy upto cursor
    std::memcpy(new_buf, buf, cursor - 1);
    std::memset(new_buf + cursor, -1, GAP_SIZE);
    std::memcpy(new_buf + cursor + GAP_SIZE, buf + cursor, buf_len - cursor);

    // Free original buffer and replace with new buffer
    free(buf);
    buf = new_buf;
    buf_len += GAP_SIZE;
    
    buf[cursor++] = new_char;
    gap--;
    return 0;
}

int Membuf::moveCursor(int offset) {
    if(cursor + offset > buf_len || cursor + offset < 0) {
        return -1;
    }
    
    if(gap == 0) {
        cursor += offset;
        return 0;
    }

    // Move right
    if(offset > 0) {
        for(int i = 0; i < std::abs(offset); i++) {
            cursor++;
            buf[cursor] = buf[cursor + gap];
            buf[cursor - 1] = -1;
        }
    }

    // Move left
    for(int i = 0; i < std::abs(offset); i++) {
        cursor--;
        buf[cursor + gap] = buf[cursor];
        buf[cursor] = -1;
    }
    return 0;
}

int Membuf::removeCharacter() {
    if(moveCursor(-1) == 0) {
        buf[cursor] = -1;
        gap++;
        return 0;
    }
    return -1;
}

int Membuf::replaceChar(char new_char) {
    if(cursor == 0) {return -1;}
    buf[cursor - 1] = new_char;
    return 0;
}

char* Membuf::getBuf() {
    return buf;
}

size_t Membuf::getSize() {
    return buf_len;
}

Membuf::~Membuf() {
    free(buf);
}
