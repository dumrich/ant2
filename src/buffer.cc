#include <buffer.hh>

Buffer::Buffer() {
    empty = true;
    isDirty = false;
}

Buffer::Buffer(CommandPath file) : _buf(file.path) {
    filePath = file.path;
    if(file.exists) {
        empty = false;
    }
}