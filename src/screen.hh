#ifndef SCREEN_HH
#define SCREEN_HH

#define ANT_MIN_LINES 30
#define ANT_MIN_COLS 40

#include <termios.h>

/*
  Screen operates in a separate thread
  - Buffer in RWLock while display updates
  - Eventually handles terminal resize
 */

enum CursorMode {
    DEFAULT,
    INVISIBLE,
    BLINK,
    BLINK_BAR
};

enum TermMode {
    CANNONICAL = 0,
    RAW = 1
};


struct RelativeSize {
    unsigned short int height;
    unsigned short int width;
};

struct PixSize {
    unsigned short int height;
    unsigned short int width;
};

struct Cursor {
    enum CursorMode mode;
    unsigned short int x_pos;
    unsigned short int y_pos;

    Cursor(enum CursorMode m);

    void setCursor(enum CursorMode m);
    void setPos(unsigned short int x_pos, unsigned short int y_pos);

    CursorMode getCursor();
    unsigned int getPos(); // First 16 bits is X, second is Y
};

class Terminal {
private:
    RelativeSize rs;
    PixSize ps; // TODO

    TermMode term_mode = TermMode::CANNONICAL;

    struct termios orig_termios;

    static void flush();
    
public:
    Cursor* cursor;

    Terminal();
    int set_raw();
    int set_cannonical();

    static void screen_alt();
    static void screen_main();

    ~Terminal();
};

// Pthreads initial render
void* render_display(void*);
#endif
