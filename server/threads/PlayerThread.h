

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
    std::string car_type;
    std::queue<InfoBlock> eventQ;
    int id;

    SenderThread sender;
    PlayerThread(Socket &my_skt, InfoBlock& ib);
    void close() override;
};


#endif //MICROMACHINES_PLAYERTHREAD_H
