#ifndef EDITOR_HH
#define EDITOR_HH

#include <pthread.h>
#include <queue>
#include "buffer.hh"
#include "screen.hh"
#include "config/config.hh"
#include "cmd.hh"

//void* display_thread(void*);
//void* editor_thread(void*);
//void* input_thread(void*);

class Editor {
private:
    std::vector<Buffer*> buffers;

    Buffer** focus_buffer;
    //pthread_mutex_t focus_mutex;
    //pthread_cond_t focus_update_display;

    Terminal screen;

    //pthread_t tids[NUM_THREADS];
public:

    Editor(AntFlags& args);
    ~Editor();

    void run();
};

#endif
