#include <iostream>
#include <stdexcept>
#include <utils/gapbuf.hh>
#include <editor.hh>
#include <cmd.hh>

int main(int argc, char** argv) {
    // AntFlags f(argc, argv);
    // auto files = f.getFiles();
    Editor<char> e;

    e.setup_interface(); // Initialize terminal, buffers, and collect input

    return e(); 
}