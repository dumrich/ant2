#ifndef CMD_HH
#define CMD_HH

#include <vector>
#include <getopt.h>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

const struct option options[] = {
    {"help", no_argument, nullptr, 'h'},
    {"files", required_argument, nullptr, 'f'},
    {nullptr, 0, nullptr, 0} // Last element must be all zeros
};

const std::string helpMessage = "Usage: ant2 [-h]... [-f=]FILES\nAnother Pocket Text Editor.\nExample: ant2 hello.c hello2.c";

struct CommandPaths {
    bool exists = false;
    bool is_dir = false;

    fs::path path;

    CommandPaths(fs::path p) {
        path = p;
        if(fs::exists(p)) {
            exists = true;
            if(fs::is_directory(p)) {
                is_dir = true;
            }
        }
    }
};

class AntFlags {
private:
    uint16_t flags; // TODO: Store flag state
    std::vector<CommandPaths> files;

public:
    AntFlags(int argc, char** argv);

    std::vector<std::string> getFiles();

    void _print_flags();
};

#endif
