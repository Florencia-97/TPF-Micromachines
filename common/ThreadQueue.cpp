

#include "ThreadQueue.h"

void ThreadQueue::push(std::string elem){
    std::unique_lock<std::mutex> lock(this->mtx);
    this->queue.push(elem);
}

std::string ThreadQueue::pop(){
    std::unique_lock<std::mutex> lock(this->mtx);
    std::string comp = this->queue.front();
    this->queue.pop();
    return comp;

}

bool ThreadQueue::isEmpty(){
    return this->queue.empty();
}