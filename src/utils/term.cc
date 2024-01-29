#include <iostream>
#include <ncurses.h>
#include "term.hh"
#include "input.hh"

Terminal::Terminal() {
    setCursorShape(CURSOR_MODE::Block);
    // Set terminal size
    getmaxyx(stdscr, size.rows, size.cols);   
}

Terminal::~Terminal() {
    endwin();

}

void Terminal::init_screen() {
    initscr();
    raw();          // Disable line buffering
    keypad(stdscr, TRUE);  // Enable special keys
    noecho();       // Don't display input characters
    curs_set(0);    // Hide the cursor
}

void Terminal::setCursorShape(CURSOR_MODE shape) {
    cursor_mode = shape;
    switch (shape) {
        case CURSOR_MODE::Block:
            std::cout << "\e[0 q";  // Escape sequence for block cursor
            break;
        case CURSOR_MODE::Underline:
            std::cout << "\e[4 q";  // Escape sequence for underline cursor
            break;
        case CURSOR_MODE::Line:
            std::cout << "\e[6 q";  // Escape sequence for line cursor
            break;
        case CURSOR_MODE::BlinkingBlock:
            std::cout << "\e[2 q";  // Escape sequence for blinking block cursor
            break;
    }
}

void Terminal::interface_loop(AsyncQueue<char>& queue) {
    char c;
    while((c = getch())) {
        // Resize window
        getmaxyx(stdscr, size.rows, size.cols);

        // Returned quit code. Only way to fail.
        if(!queue.push(c)) {
            break;
        }
    }
}