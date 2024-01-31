#pragma once

#include <vector>
#include <string>
#include <pthread.h>
#include <utils/term.hh>
#include <utils/async_queue.hh>

#define QUIT_CODE 0x13

#define UI_THREAD 0
#define EDITOR_THREAD 1

template <typename T>
class Editor {
private:
    Terminal term;

    AsyncQueue<T>& _input_queue;

    pthread_t threads[2];
    // vector<Buffer> buffers;
    
    void input_loop(void);
    friend void* input_thread(void*);

public:
    Editor();
    // Editor(vector<std::string>)
    ~Editor();

    // Capture screen inputs

    void setup_interface(void);

    int operator()(void);
};

#include <editor.tpp>