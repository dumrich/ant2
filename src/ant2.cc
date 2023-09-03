#include <iostream>
#include <cstring>
#include <unistd.h>
#include "cmd.hh"
#include "screen.hh"

int main(int argc, char** argv) {
    // Capture files to open
    AntFlags f(argc, argv); 

    Terminal* t = new Terminal();
    t->set_raw();
    t->flush();

    sleep(3);

    delete t;
}
