#include "../common/infostream/Protocol.h"
#include "Receiver.h"

Receiver::Receiver(Socket& skt, SafeQueue<InfoBlock>* queue):
    skt(skt) {
    this->queue = queue;
}

void Receiver::_run() {
    while (this->isAlive()){
        InfoBlock news;
        if (! Protocol::recvMsg(&skt, news)){
            this->close();
            break;
        }
        this->queue->push(news);
    }
    this->close();
}

//it doesnt needs to close the socket, i believe
Receiver::~Receiver() {}

