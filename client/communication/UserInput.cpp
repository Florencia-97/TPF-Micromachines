#include <SDL2/SDL.h>
#include <iostream>

#include "UserInput.h"
#include "../../config/constants.h"
#include "../common/SafeQueue.h"

UserInput::UserInput(SafeQueue<InfoBlock> *safeQueueServer,
                     std::queue<SDL_Event> *text_queue) {
    // TODO assign to class safeQueue a way of being past without pointer
    this->keyboard_input = safeQueueServer;
  this->local_queue = text_queue;
}

void UserInput::_run(){
    SDL_Event e;
    std::cout << "Starting to read input keys from client\n";
    while (this->isAlive()){
        while( SDL_PollEvent(&e) != 0 && this->isAlive()) {
            _rcvKeyInput(e);
        }
    }
}

void UserInput::_rcvKeyInput(SDL_Event &e){
    if ( e.type == SDL_QUIT){
        InfoBlock ib;
        ib[ACTION_TYPE] = QUIT;
        this->keyboard_input->push(ib);
        this->close();
        return;
    }
    std::string eventType;
    bool forServer = true;

    switch (e.type){
      case SDL_MOUSEBUTTONDOWN:;
            local_queue->push(e);
            forServer = false;
            eventType = MOUSE_BUTTON_DOWN;
            break;
      case SDL_MOUSEBUTTONUP:
            local_queue->push(e);
            forServer = false;
            eventType = MOUSE_BUTTON_UP;
            break;
    }

    if( e.type != SDL_KEYDOWN) return;

    // For keys
    switch (e.key.keysym.sym) {
        case SDLK_UP:
            eventType = UP;
            break;
        case SDLK_DOWN:
            eventType = DOWN;
            break;
        case SDLK_LEFT:
            eventType = LEFT;
            break;
        case SDLK_RIGHT:
            eventType = RIGHT;
            break;
        default:
            forServer = false;
            local_queue->push(e);
    }
    //Creating infoblock to queue in EventsQueue
    InfoBlock ib;
    ib[ACTION_TYPE] = eventType;
    if (forServer) this->keyboard_input->push(ib);
}

void UserInput::close() {
    this->keyboard_input->setOpen(false);
    BaseThread::close();
}