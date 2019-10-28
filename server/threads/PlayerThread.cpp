

#include "PlayerThread.h"

void PlayerThread::_run() {
    while (!this->isClosed()){

    }
}

void PlayerThread::close() {
    skt.closeSd();
    BaseThread::close();
}

PlayerThread::PlayerThread(Socket &my_skt) {
    this->skt = std::move(my_skt);
}
