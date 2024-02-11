#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <utils/gapbuf.hh>
#include <cmd.hh>

namespace fs = std::filesystem;

class Buffer {
private:
    fs::path filePath;

    bool empty = true; // Or is empty
    bool isDirty = false;

    GapBuffer<char> _buf;
public:
    Buffer();
    Buffer(CommandPath file);

    bool save_file();
    std::vector<std::string> get_lines(int starting, int ending);


};