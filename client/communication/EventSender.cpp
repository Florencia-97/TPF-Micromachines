#include "EventSender.h"

#include "../common/Event.h"
#include "../../common/stream/Protocol.h"
#include "../../common/stream/InfoBlock.h"

EventSender::EventSender(Socket& skt, SafeEventQueue& queue) :
        alive(true) ,skt(skt), queue(queue) {}

bool _isFinalEvent(Event& event){
    return false; // Discuss how the event sends me the quit action!
}

void EventSender::run() {
    while (this->alive){
        Event event = queue.pop();
        if (_isFinalEvent(event)){
            this->alive = false;
            break;
        }
        InfoBlock infoBlock(event.toYamlString(), false ); //event should convert to InfoBlock?
        if (Protocol::sendMsg(&this->skt, infoBlock) == false){
            this->alive = false;
            break;
        }
    }
}

void EventSender::stop() {
    this->alive = false;
}

bool EventSender::isAlive(){
    return this->alive;
}

EventSender::~EventSender() {}

