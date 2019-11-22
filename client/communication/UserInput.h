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
    std::queue<SDL_Event> *mouse_queue;
    std::queue<SDL_Event> *writing_queue;
    std::queue<std::string> *sound_queue;
    std::queue<std::string> *video_queue; // Is there a better way ?
    void _run() override;
    std::map<char, bool> key_pressings;
    std::condition_variable *close_window;

public:
    bool exit;
    bool isScript;

  UserInput(SafeQueue<InfoBlock> *q_keyboard, std::queue<SDL_Event> *mouse_queue,
            std::queue<SDL_Event> *text_queue, std::queue<std::string> *sound_queue,
            std::condition_variable *close_window, std::queue<std::string> *video_queue);
    void _rcvKeyInput(SDL_Event &e);
    void close() override;
};


#endif //MICROMACHINES_USERINPUT_H
