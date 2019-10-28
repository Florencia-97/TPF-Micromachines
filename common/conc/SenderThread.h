

#ifndef MICROMACHINES_SENDERTHREAD_H
#define MICROMACHINES_SENDERTHREAD_H

#include "BaseThread.h"
#include "../infostream/Protocol.h"
#include "../SafeQueue.h"

class SenderThread : public BaseThread {
    Socket *skt;

    void _run() override;

public:
    SafeQueue<InfoBlock> to_send;

    explicit SenderThread(Socket* s) : skt(s){};

    void close() override;

};


#endif //MICROMACHINES_SENDERTHREAD_H
