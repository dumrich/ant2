#ifndef BUFFER_HH
#define BUFFER_HH

#include "utils/gapbuf.hh"
#include "config/config.hh"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;


class Buffer {
private:
    bool is_shown = true;
    Membuf* text_buffer;
    BufferType btype;
    
    // File stuff
    fs::path file_path;
    std::fstream file;
    bool is_dirty;

public:
    Buffer(fs::path&);
    Buffer();
    ~Buffer();

    bool get_shown();
    void set_shown(bool);

    Membuf* get_buf();

    static BufferType getBufferType(fs::path& ext);
};

#endif
