#ifndef GAPBUF_HH
#define GAPBUF_HH

#include <cstddef>

// simple internal gap buffer
class Membuf {
private:
    size_t buf_len;
    
    char* buf;
    int cursor;

public:
    Membuf(char* _buf, size_t _buf_len) : buf(_buf), buf_len(_buf_len) {};

    int insert(char new_char);
    int moveCursor(int offset); // -1 or +1

    int removeCharacter();
    int replaceChar(char new_char);

    // To write everything to file
    char* getBuf();
};

#endif
