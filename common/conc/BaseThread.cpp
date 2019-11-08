

#include "BaseThread.h"

void BaseThread::close() {
    this->alive.store(false);
}

void BaseThread::join() {
    if (running){
        this->t.join();
        running = false;
    }
}

bool BaseThread::isAlive() {
    return alive.load();
}

void BaseThread::run() {
    running = true;
    this->t = std::thread(&BaseThread::_run, this);
}

BaseThread::BaseThread() : alive(true) {
    running = false;
}

bool BaseThread::isRunning() {
    return running;
}

BaseThread::BaseThread(BaseThread&& other) {
    this->alive.store(other.alive);
    this->running = other.running;
    this->t= std::move(other.t);
}

BaseThread & BaseThread::operator=(BaseThread&& other) {
    this->alive.store(other.alive);
    this->running = other.running;
    this->t= std::move(other.t);
    return *this;
}

void BaseThread::sleep(float timestep) {
    std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000*timestep)));
}
