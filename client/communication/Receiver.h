#ifndef MICROMACHINES_RECEIVER_H
#define MICROMACHINES_RECEIVER_H

#include <queue>

#include "../common/conc/BaseThread.h"
#include "../../common/infostream/Socket.h"
#include "../../common/infostream/InfoBlock.h"
#include "../../common/SafeQueue.h"

//It recvs from its socket by protocol the new view to draw
// It updates de view to be rendered

class Receiver: public BaseThread {
    Socket& skt;
    SafeQueue<InfoBlock>* queue;
    void _run() override;

    public:
    Receiver(Socket& skt, SafeQueue<InfoBlock>* queue);
    ~Receiver();


};

#endif //MICROMACHINES_RECEIVER_H
