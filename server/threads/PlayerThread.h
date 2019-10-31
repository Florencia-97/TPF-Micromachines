

#ifndef MICROMACHINES_PLAYERTHREAD_H
#define MICROMACHINES_PLAYERTHREAD_H

#include <queue>

#include "../../common/infostream/Socket.h"
#include "../../common/conc/SenderThread.h"
#include "../../common/infostream/InfoBlock.h"
#include "../../common/infostream/Protocol.h"
#include "../../common/SafeQueue.h"

class PlayerThread : public BaseThread {

    void _run() override;
    Socket skt;

public:
    std::queue<InfoBlock> eventQ; //TODO change to normal queue (non blocking)
    SenderThread sender;

    explicit PlayerThread(Socket &my_skt);

    void close() override;
};


#endif //MICROMACHINES_PLAYERTHREAD_H
