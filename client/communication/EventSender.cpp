#include "EventSender.h"

#include "../common/Event.h"
#include "../../common/stream/Protocol.h"
#include "../../common/stream/InfoBlock.h"

EventSender::EventSender(Socket& skt, SafeEventQueue& queue) :
        alive(true) ,skt(skt), queue(queue) {}

bool _isFinalEvent(Event& event){
    return false; // Discuss how the event sends me the quit action!
}

void EventSender::_run() {
    while (this->isAlive()){
        Event event = queue.pop();
        if (_isFinalEvent(event)){
            break;
        }
        InfoBlock infoBlock(event.toYamlString(), false ); //event should convert to InfoBlock?
        if (Protocol::sendMsg(&this->skt, infoBlock) == false){
            break;
        }
    }
    close();
}

