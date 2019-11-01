#include "PlayerThread.h"

PlayerThread::PlayerThread(Socket &my_skt) : sender(&skt) {
    this->skt = std::move(my_skt);
}

void PlayerThread::_run() {
    std::cout << "New player running";
    this->sender.run();
    bool socketWorking = true;
    while (this->isAlive() && socketWorking && skt.isValid()){
        InfoBlock info;
        socketWorking = Protocol::recvMsg(&skt, info);
        if (socketWorking) this->eventQ.push(info);
        else break;
    }
}

void PlayerThread::close(){
    if (!this->isAlive()) return;
    skt.closeSd();
    sender.close();
    sender.join();
    // This closes atomic alive ! Needed if i want to redifine close of base thread
    BaseThread::close();
}

PlayerThread::~PlayerThread(){
    close();
}
