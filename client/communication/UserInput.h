#ifndef MICROMACHINES_USERINPUT_H
#define MICROMACHINES_USERINPUT_H

#include <SDL2/SDL.h>
#include "../common/conc/BaseThread.h"
#include "../common/SafeQueue.h"
#include "../common/infostream/InfoBlock.h"

/*
 This thread reads user input.
 It adds event as infoblock to the safe queue received as parameter
 */

class UserInput : public BaseThread {
    SafeQueue<InfoBlock>* safeQueueServer;
    SafeQueue<InfoBlock>* safeQueueClient;
public:
    UserInput(SafeQueue<InfoBlock>* safeQueueServer, SafeQueue<InfoBlock>* safeQueueClient);
    void _rcvKeyInput(SDL_Event &e);
    void _run() override;
    ~UserInput();

};


#endif //MICROMACHINES_USERINPUT_H
