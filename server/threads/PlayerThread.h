

#ifndef MICROMACHINES_PLAYERTHREAD_H
#define MICROMACHINES_PLAYERTHREAD_H

#include "../../common/Socket.h"
#include "../../common/BaseThread.h"
#include "../../common/InfoBlock.h"
#include "../../common/Protocol.h"
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
