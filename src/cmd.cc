#include "cmd.hh"
#include <bits/getopt_core.h>
#include <iostream>
#include <cstdlib>
#include <ostream>

AntFlags::AntFlags(int argc, char** argv) {
    int opt;
    int optionIndex;
    std::string cmd_files;
    
    while((opt = getopt_long(argc, argv, "hf:", options, &optionIndex)) != -1)
    {
        switch(opt) {
        case 'f':
            cmd_files = optarg;
            break;
        case 'h':
        default:
            std::cout << helpMessage << std::endl;
            std::exit(1);
        }
    }

    for(int index = optind; index < argc; index++) {
        fs::path file_arg = argv[index];
        if(!file_arg.empty()) {
            CommandPaths p(file_arg);
            files.push_back(p);
        }
    }

    size_t start = 0;
    size_t end = 0;
    // Parse file comma separated file list
    while((end = cmd_files.find(",", start)) != std::string::npos) {
        fs::path sub = cmd_files.substr(start, end - start);
        CommandPaths d(sub);
        files.push_back(d);
        start = end + 1;
    }

    if(start < cmd_files.size()) {
        // final token
        fs::path sub = cmd_files.substr(start, cmd_files.size() - start);
        CommandPaths d(sub);
        files.push_back(d);
    }
}
