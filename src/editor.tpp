#include "editor.hh"
#include <buffer.hh>
#include <ncurses.h>
#include <stdexcept>

template <typename T>
void Editor<T>::input_loop(void) {
    char c;
    while((c = getch())) {
        // Resize window
        term.update_size();

        // Returned quit code. Only way to fail.
        if(c == QUIT_CODE) {
            break;
        }

        _input_queue->push(c);
    }
    _input_queue->push(-1);
}

void* input_thread(void* instance) {
    Editor<char>* i = static_cast<Editor<char>*>(instance);

    i->term.init_screen();
    i->input_loop();
    return nullptr;
}

template <typename T>
void Editor<T>::setup_interface(void) {
    if(pthread_create(&threads[UI_THREAD], nullptr, input_thread, this) != 0) {
        throw std::runtime_error("Could not create thread using `pthread_create`");
    }

    // pthread_join(threads[UI_THREAD], nullptr);
    
    // TODO: Create another thread to handle rendering
}

template <typename T>
int Editor<T>::operator()(void) {
    // Handle keystrokes in main thread
    // TODO: Pass to rendering thread

    T c;
    
    while((c = _input_queue->pop()) != -1) {
        // std::string s = std::to_string(c);
        // term.print_screen(s);
    }

    return 0;
}

template <typename T>
Editor<T>::Editor() {
    _input_queue = new AsyncQueue<T>();
}

template <typename T>
Editor<T>::Editor(std::vector<CommandPaths> p) {
    for(auto& cp : p) {
        auto b = new Buffer(cp);
        buffers.push_back(b);
    }
    _input_queue = new AsyncQueue<T>();
}

template <typename T>
Editor<T>::~Editor() {
    delete _input_queue;
    for(auto* b : buffers) {
        delete b;
    }
}