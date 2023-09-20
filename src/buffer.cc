#include "buffer.hh"
#include <iostream>
#include <cstdlib>

Buffer::Buffer(fs::path& p) : file(p, std::ios::in | std::ios::out), file_path(p) {
    if(!file.is_open()) {
        std::cerr << "Could not open file";
        std::exit(1);
    }

    // Determine the size of the file
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    char* text_buf = (char*)std::malloc(fileSize + GAP_SIZE);

    // TODO: Large file no slurp
    file.read(text_buf, fileSize);

    // Clean by default
    is_dirty = false;

    // Setup membuf
    text_buffer = new Membuf(text_buf, fileSize + GAP_SIZE, GAP_SIZE);

    // Buffer Type
    auto placeholder = p.extension();
    btype = getBufferType(placeholder);
}
