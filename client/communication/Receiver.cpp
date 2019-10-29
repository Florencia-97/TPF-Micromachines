#include "Receiver.h"
#include "../common/infostream/Protocol.h"

Receiver::Receiver(Socket& skt): alive(true), skt(skt) {}

void Receiver::run() {
    while (this->isAlive()){
        InfoBlock news;
        if (Protocol::recvMsg(&skt, news)){
            this->alive = false;
            break;
        }
        this->infoBlock = news; // do we need a wrapper and mutex here?
    }
}

Receiver::~Receiver() {}

