#include <iostream>
#include <ostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include "screen.hh"

Cursor::Cursor(enum CursorMode m) : mode{m} {}

void Cursor::setCursor(enum CursorMode m) {
    switch(m) {
    case DEFAULT:
        std::cout << "\033[0 q";
        break;
    case INVISIBLE:
        std::cout << "\033[?25l";
        break;
    case BLINK_BAR:
        std::cout << "\033[5 q";
        break;
    case BLINK:
        std::cout << "\033[1 q";
        break;
    }
}

// Does no bounds check
void Cursor::setPos(unsigned short x_pos, unsigned short y_pos) {
    this->x_pos = x_pos;
    this->y_pos = y_pos;

    fprintf(stdout, "\033[%d;%df", y_pos, x_pos);
}

unsigned int Cursor::getPos() {
    return (((unsigned int)x_pos << 16) | (unsigned int)y_pos);
}

CursorMode Cursor::getCursor() {
    return mode;
}


void enableRawMode() {
  struct termios raw;
  tcgetattr(STDIN_FILENO, &raw);

  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

Terminal::Terminal() {
    tcgetattr(STDIN_FILENO, &orig_termios);

    struct winsize win;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);

    rs = {win.ws_row, win.ws_col};
    cursor = new Cursor(CursorMode::DEFAULT);

    screen_alt();
}

Terminal::~Terminal() {
    //cursor->setCursor(CursorMode::DEFAULT);
    delete cursor;
    set_cannonical();
    screen_main();
}

int Terminal::set_raw() {
    enableRawMode();
    flush();
    term_mode = TermMode::RAW;

    return 0;
}

int Terminal::set_cannonical() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    term_mode = TermMode::RAW;
    return 0;
}

void Terminal::screen_alt() {
    std::cout << "\033[?1049h";
}

void Terminal::screen_main() {
    std::cout << "\033[?1049l";
}

void Terminal::flush() {
    std::cout << std::flush;
}
