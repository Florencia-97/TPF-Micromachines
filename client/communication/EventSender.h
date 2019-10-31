#ifndef MICROMACHINES_EVENTSENDER_H
#define MICROMACHINES_EVENTSENDER_H

#include "../../common/SafeQueue.h"
#include "../../common/infostream/Socket.h"
#include "../common/conc/BaseThread.h"
#include "../common/infostream/InfoBlock.h"

/*
 * This class has a reference to a SafeEventQueue
 * It sends what is poped to the server
 * It pops until a suicidal pill is poped
 * It stops running at that moment
 */

class EventSender: public BaseThread{
    Socket& skt;
    SafeQueue<InfoBlock>* safeQueue;
    void _run() override;

public:
    EventSender(Socket& skt, SafeQueue<InfoBlock>* safeQueue);
    ~EventSender();
};


#endif //MICROMACHINES_EVENTSENDER_H
