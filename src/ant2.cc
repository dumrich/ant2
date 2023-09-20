#include <iostream>
#include <cstring>
#include <unistd.h>
#include "cmd.hh"
#include "editor.hh"

int main(int argc, char** argv) {
    // Capture files to open
    AntFlags f(argc, argv); // Capture Command Line Args 

    Editor* ant = new Editor(f);

    delete ant;
}
