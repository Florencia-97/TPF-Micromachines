

#ifndef MICROMACHINES_RENDERTHREAD_H
#define MICROMACHINES_RENDERTHREAD_H

#include "../common/conc/BaseThread.h"
#include "../common/SafeQueue.h"
#include "../common/infostream/InfoBlock.h"
#include <SDL2/SDL.h>

class RenderThread {
    void _run() ;

public:
    //queue<InfoBlock> renderQueue;

};


#endif //MICROMACHINES_RENDERTHREAD_H
