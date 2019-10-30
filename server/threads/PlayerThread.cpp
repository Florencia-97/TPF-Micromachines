#include "PlayerThread.h"

PlayerThread::PlayerThread(Socket &my_skt) : sender(&skt) {
    this->skt = std::move(my_skt);
}

void PlayerThread::_run() {
    bool s = true;
    this->sender.run();
    while (!this->isAlive() && s && skt.isValid()){
        InfoBlock info;
        s = Protocol::recvMsg(&skt, info);
        if (s) this->eventQ.push(info);
    }
    close();
}

void PlayerThread::close(){
    if (!this->isAlive()) return;
    skt.closeSd();
    sender.close();
    sender.join();
    BaseThread::close();
}
