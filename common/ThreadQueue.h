

#ifndef MICROMACHINES_THREADQUEUE_H
#define MICROMACHINES_THREADQUEUE_H

#include <queue>
#include <string>
#include <mutex>

class ThreadQueue {
    std::queue<std::string> queue;
    std::mutex mtx;
public:
    void push(std::string elem);
    std::string pop();
    bool isEmpty();
};


#endif //MICROMACHINES_THREADQUEUE_H
