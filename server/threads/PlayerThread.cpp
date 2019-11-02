#include "../../config/constants.h"

#include "PlayerThread.h"

PlayerThread::PlayerThread(Socket &my_skt, InfoBlock& ib) :
    sender(&skt), car_type(ib.getString(CAR_TYPE)) {
    this->skt = std::move(my_skt);
}

void PlayerThread::_run() {
    std::cout << "New player running\n";
    this->sender.run();
    bool socketWorking = true;
    while (this->isAlive() && socketWorking && skt.isValid()){
        InfoBlock info;
        socketWorking = Protocol::recvMsg(&skt, info);
        if (socketWorking) this->eventQ.push(info);
        else break;
    }
    std::cout << "Leaving here for good!\n";
    close();
}

void PlayerThread::close(){
    if (!this->isAlive()) return;
    skt.closeSd();
    sender.close();
    sender.join();
    BaseThread::close();
}