#ifndef MICROMACHINES_USERINPUT_H
#define MICROMACHINES_USERINPUT_H

#include <SDL2/SDL.h>
#include "../common/Thread.h"

/*
 This thread reads user input.

 */

class UserInput : public Thread {
    bool alive;
    void _rcvKeyInput(SDL_Event &e);

public:
    UserInput();
    virtual void run() override;
    virtual void stop() override;
    virtual bool isAlive() override;
    //~UserInput();

};


#endif //MICROMACHINES_USERINPUT_H
