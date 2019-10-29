

#include "PlayerThread.h"

void PlayerThread::_run() {
    bool s = true;
    this->sender.run();
    while (!this->isAlive() && s && skt.isValid()){
        InfoBlock info;
        s = Protocol::recvMsg(&skt, info);
        if (s) event_q.push(info);
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

PlayerThread::PlayerThread(Socket &my_skt) : sender(&skt) {
    this->skt = std::move(my_skt);
}
