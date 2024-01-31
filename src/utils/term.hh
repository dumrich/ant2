#pragma once

#include <string>

/* 
    Terminal should run in separate UI thread.
    Communicates with main editor thread through
    queue w/ mutex.
*/

enum class CURSOR_MODE {
    Block,
    Underline,
    Line,
    BlinkingBlock,
    None
};

struct TerminalSize {
    unsigned short rows;
    unsigned short cols;
};

class Terminal {
private:
    enum CURSOR_MODE cursor_mode;
    TerminalSize size;
public:
    Terminal();
    ~Terminal();

    void setCursorShape(CURSOR_MODE);
    void update_size();

    // Redisplay and recapture screen size
    void init_screen();

    void print_screen(std::string s);
};