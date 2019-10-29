#ifndef MICROMACHINES_EVENTSENDER_H
#define MICROMACHINES_EVENTSENDER_H

#include "../../common/SafeQueue.h"
#include "../../common/stream/Socket.h"
#include "../common/conc/BaseThread.h"

/*
 * This class has a reference to a SafeEventQueue
 * It sends what is poped to the server
 * It pops until a suicidal pill is poped
 * It stops running at that moment
 */

class EventSender: public BaseThread{
    Socket& skt;
    SafeEventQueue& queue;
    virtual void _run() override;

public:
    EventSender(Socket& skt, SafeEventQueue& queue);

    ~EventSender();
};


#endif //MICROMACHINES_EVENTSENDER_H
