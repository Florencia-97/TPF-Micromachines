

#ifndef MICROMACHINES_PLAYERTHREAD_H
#define MICROMACHINES_PLAYERTHREAD_H

#include "../../common/Socket.h"
#include "../../common/BaseThread.h"
#include "../../common/InfoBlock.h"
#include <queue>

class PlayerThread : public BaseThread {
public:
    std::queue<InfoBlock> event_q;
};


#endif //MICROMACHINES_PLAYERTHREAD_H
