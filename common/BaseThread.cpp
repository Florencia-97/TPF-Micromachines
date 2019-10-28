

#include "BaseThread.h"

void BaseThread::close() {
    this->keep_running.store(false);
}

void BaseThread::join() {
    this->t.join();
}

bool BaseThread::isClosed() {
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
