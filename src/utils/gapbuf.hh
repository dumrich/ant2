#ifndef GAPBUF_HH
#define GAPBUF_HH

#include <cstddef>
#include <config.hh>


// simple internal gap buffer
class Membuf {
private:
    size_t buf_len;
    
    char* buf;
    size_t cursor;

    size_t gap;
    
public:
    Membuf(char* b, size_t l, size_t gap);
    ~Membuf();

    int insert(char new_char);
    int moveCursor(int offset); // - or +

    int removeCharacter();
    int replaceChar(char new_char);

    // To write everything to file
    char* getBuf();
    size_t getSize();
};

#endif
