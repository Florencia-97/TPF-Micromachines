

#include "PlayerThread.h"

void PlayerThread::_run() {
    bool s = true;
    while (!this->isClosed() && s && skt.isValid()){
        InfoBlock info;
        s = Protocol::recvMsg(&skt, info);
        if (s) event_q.emplace(info.srcString(),false);
    }
    close();
}

void PlayerThread::close(){
    if (!this->isClosed()) return;
    skt.closeSd();
    sender.close();
    sender.join();
    BaseThread::close();
}

PlayerThread::PlayerThread(Socket &my_skt) : sender(&skt) {
    this->skt = std::move(my_skt);
}
