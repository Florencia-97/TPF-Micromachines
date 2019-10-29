#ifndef MICROMACHINES_RECEIVER_H
#define MICROMACHINES_RECEIVER_H

#include "../../common/infostream/Socket.h"
#include "../../common/infostream/InfoBlock.h"
#include "../common/conc/BaseThread.h"

//It recvs from its socket by protocol the new view to draw
// It updates de view to be rendered

class Receiver: public BaseThread {
    bool alive;
    Socket& skt;
    InfoBlock infoBlock; // discuss which structure are we going to use!

    public:
    Receiver(Socket& skt);
    virtual void run() override;
    ~Receiver();


};


#endif //MICROMACHINES_RECEIVER_H
