#ifndef MICROMACHINES_USERINPUT_H
#define MICROMACHINES_USERINPUT_H

#include <SDL2/SDL.h>
#include "../common/conc/BaseThread.h"
#include "../common/SafeQueue.h"
#include "../common/infostream/InfoBlock.h"
#include <map>
/*
 This thread reads user input.
 It adds event as infoblock to the safe mouse_queue received as parameter
 */

class UserInput : public BaseThread {
    SafeQueue<InfoBlock>* keyboard_input;
    SafeQueue<InfoBlock>* mouse_input;
  std::queue<SDL_Event> *mouse_queue;
  std::queue<SDL_Event> *writing_queue;
    void _run() override;
    std::map<char, bool> key_pressings;

public:
  UserInput(SafeQueue<InfoBlock> *q_keyboard,
            SafeQueue<InfoBlock> *q_mouse,
            std::queue<SDL_Event> *mouse_queue,
            std::queue<SDL_Event> *text_queue);
    void _rcvKeyInput(SDL_Event &e);
    void close() override;

};


#endif //MICROMACHINES_USERINPUT_H
