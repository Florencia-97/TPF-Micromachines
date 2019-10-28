

#ifndef MICROMACHINES_PLAYERTHREAD_H
#define MICROMACHINES_PLAYERTHREAD_H

#include "../../common/infostream/Socket.h"
#include "../../common/conc/SenderThread.h"
#include "../../common/infostream/InfoBlock.h"
#include "../../common/infostream/Protocol.h"
#include <queue>
#include "../../common/SafeQueue.h"

class PlayerThread : public BaseThread {

    void _run() override;
    Socket skt;

public:
    SafeQueue<InfoBlock> event_q; //TODO change to normal queue (non blocking)
    SenderThread sender;

    PlayerThread(Socket &my_skt);

    void close() override;
};


#endif //MICROMACHINES_PLAYERTHREAD_H
