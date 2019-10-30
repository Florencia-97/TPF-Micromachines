#include "EventSender.h"

#include "../../common/infostream/Protocol.h"
#include "../../common/infostream/InfoBlock.h"

EventSender::EventSender(Socket& skt, SafeQueue<InfoBlock>* safeQueue) :
    skt(skt) {
    this->safeQueue = safeQueue;
}

bool _isFinalEvent(InfoBlock& ib){
    std::string actionType = ib.get<std::string>("action");
    return actionType.compare("QUIT") == 0; // Discuss how the event sends me the quit action!
}

void EventSender::_run() {
    while (this->isAlive()){
        InfoBlock ib = this->safeQueue->pop();
        if (_isFinalEvent(ib)){
            break;
        }
        if (Protocol::sendMsg(&this->skt, ib) == false){
            break;
        }
    }
    close();
}

EventSender::~EventSender() {}
