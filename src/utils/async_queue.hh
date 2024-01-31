/* Full header implementation of an asynchronous queue */

#pragma once

#include <queue>
#include <pthread.h>

template <typename T>
class AsyncQueue {
private:
    std::queue<T> _queue;

    pthread_mutex_t _queue_mutex;
    pthread_cond_t _queue_condition;

public:
    AsyncQueue() {
        // TODO: Error handling
        pthread_mutex_init(&_queue_mutex, NULL);
        pthread_cond_init(&_queue_condition, NULL);
    }

    void push(T val) {
        pthread_mutex_lock(&_queue_mutex);
        // Critical Section
        _queue.push(val);

        pthread_cond_signal(&_queue_condition);
        pthread_mutex_unlock(&_queue_mutex);
        return;
    }

    // Modified pop, returns first elements
    T pop() {
        pthread_mutex_lock(&_queue_mutex);
        while(_queue.size() == 0) {
            pthread_cond_wait(&_queue_condition, &_queue_mutex);
        }
        T ret = _queue.front();
        _queue.pop();
        pthread_mutex_unlock(&_queue_mutex);

        return ret;
    }
};