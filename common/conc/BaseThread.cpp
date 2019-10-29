

#include "BaseThread.h"

void BaseThread::close() {
    this->keep_running.store(false);
}

void BaseThread::join() {
    this->t.join();
}

bool BaseThread::isAlive() {
    return keep_running.load();
}

void BaseThread::run() {
    running = true;
    this->t = std::thread(&BaseThread::_run, this);
}

BaseThread::BaseThread() : keep_running(true) {
    running = false;
}

bool BaseThread::isRunning() {
    return running;
}

BaseThread::BaseThread(BaseThread&& other) {
    this->keep_running.store(other.keep_running);
    this->running = other.running;
    this->t= std::move(other.t);
}

BaseThread & BaseThread::operator=(BaseThread&& other) {
    this->keep_running.store(other.keep_running);
    this->running = other.running;
    this->t= std::move(other.t);
    return *this;
}
