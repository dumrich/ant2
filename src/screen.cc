#include <iostream>
#include <ostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include "screen.hh"

Cursor::Cursor(enum CursorMode m) : mode{m} {
    fprintf(stdout, "\033[%d;%dH", 1, 1);
    fflush(stdout);
    x_pos = 1;
    y_pos = 1;
}

void enableRawMode() {
  struct termios raw;
  tcgetattr(STDIN_FILENO, &raw);
  raw.c_lflag &= ~(ECHO | ICANON);
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
