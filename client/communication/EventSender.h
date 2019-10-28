#ifndef MICROMACHINES_EVENTSENDER_H
#define MICROMACHINES_EVENTSENDER_H

#include "../../common/SafeQueue.h"
#include "../../common/stream/Socket.h"
#include "../common/Thread.h"

/*
 * This class has a reference to a SafeEventQueue
 * It sends what is poped to the server
 * It pops until a suicidal pill is poped
 * It stops running at that moment
 */

class EventSender: public Thread{
    bool alive;
    Socket& skt;
    SafeEventQueue& queue;
public:
    EventSender(Socket& skt, SafeEventQueue& queue);
    virtual void run() override;
    virtual void stop() override;
    virtual bool isAlive() override;
    ~EventSender();
};


#endif //MICROMACHINES_EVENTSENDER_H
