

#ifndef MICROMACHINES_PLAYERTHREAD_H
#define MICROMACHINES_PLAYERTHREAD_H

#include "../../common/stream/Socket.h"
#include "../../common/conc/BaseThread.h"
#include "../../common/stream/InfoBlock.h"
#include "../../common/stream/Protocol.h"
#include <queue>

class PlayerThread : public BaseThread {

    void _run() override;
    Socket skt;

public:
    std::queue<InfoBlock> event_q;
    std::queue<InfoBlock> send_to_client;

    PlayerThread(Socket &my_skt);

    void close() override;
};


#endif //MICROMACHINES_PLAYERTHREAD_H
