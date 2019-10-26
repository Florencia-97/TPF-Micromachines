#include <mutex>

#include "SafeEventQueue.h"
#include "Event.h"

SafeEventQueue::SafeEventQueue() {}

void SafeEventQueue::push(Event& event){
    std::unique_lock<std::mutex> lock(this->m);
    this->q.push(event);
    this->cv.notify_one();
}

Event SafeEventQueue::pop(){
    std::unique_lock<std::mutex> lock(this->m);
    while (this->q.empty()){
        this->cv.wait(lock);
    }
    Event comp = this->q.front();
    this->q.pop();
    return comp;
}

SafeEventQueue::~SafeEventQueue() {}
