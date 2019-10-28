

#ifndef MICROMACHINES_RECEIVERTHREAD_H
#define MICROMACHINES_RECEIVERTHREAD_H

#include "BaseThread.h"
#include "../infostream/Protocol.h"
#include <queue>

class ReceiverThread : public BaseThread {
    Socket *skt;

    void _run() override;

public:
    //TODO
    std::queue<InfoBlock> recvd;

    explicit ReceiverThread(Socket* s) : skt(s){};

};

#endif //MICROMACHINES_RECEIVERTHREAD_H
