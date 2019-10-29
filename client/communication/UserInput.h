#ifndef MICROMACHINES_USERINPUT_H
#define MICROMACHINES_USERINPUT_H

#include <SDL2/SDL.h>
#include "../common/conc/BaseThread.h"

/*
 This thread reads user input.

 */

class UserInput : public BaseThread {

    void _rcvKeyInput(SDL_Event &e);

    void _run() override;

public:

};


#endif //MICROMACHINES_USERINPUT_H
