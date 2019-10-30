

#ifndef MICROMACHINES_RENDERTHREAD_H
#define MICROMACHINES_RENDERTHREAD_H

#include "../common/conc/BaseThread.h"
#include "../common/SafeQueue.h"
#include "../common/infostream/InfoBlock.h"
#include "rendering/GameRenderer.h"
#include <SDL2/SDL.h>

class RenderThread : BaseThread {

    void _run(); //TODO HIGH RENDER LOOP CALLS gameRenderer.render() and checks frames

    GameRenderer* gameRenderer;

public:
    //queue<InfoBlock> renderQueue;

    RenderThread(GameRenderer &gr);
};


#endif //MICROMACHINES_RENDERTHREAD_H
