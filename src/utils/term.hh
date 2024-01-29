#pragma once

/* 
    Terminal should run in separate UI thread.
    Communicates with main editor thread through
    queue w/ mutex.
*/

#include <utils/async_queue.hh>
#include <pthread.h>

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

    // Redisplay and recapture screen size
    void init_screen();

    // Capture screen inputs
    void interface_loop(AsyncQueue<char>&);
};