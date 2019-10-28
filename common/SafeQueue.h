#ifndef MICROMACHINES_SAFEQUEUE_H
#define MICROMACHINES_SAFEQUEUE_H

#include <bits/stdc++.h>
#include <fstream>
#include <arpa/inet.h>
#include <condition_variable>
#include <queue>
#include <mutex>

#include "Event.h"

template <class T>
class SafeQueue{
    std::queue<T> q;
    std::mutex m;
    std::condition_variable cv;

public:
    void push(T& event);

    T pop();

};

template<class T>
void SafeQueue<T>::push(T &event) {
    std::unique_lock<std::mutex> lock(this->m);
    this->q.push(event);
    this->cv.notify_one();
}

template<class T>
T SafeQueue<T>::pop() {
    std::unique_lock<std::mutex> lock(this->m);
    while (this->q.empty()){
        this->cv.wait(lock);
    }
    T comp = this->q.front();
    this->q.pop();
    return comp;
}

#endif //MICROMACHINES_SAFEQUEUE_H
