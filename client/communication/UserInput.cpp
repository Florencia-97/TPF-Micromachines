#include <SDL2/SDL.h>
#include <iostream>

#include "UserInput.h"
#include "../../config/constants.h"
#include "../common/SafeQueue.h"

UserInput::UserInput(SafeQueue<InfoBlock> *safeQueueServer,
                     SafeQueue<InfoBlock> *safeQueueClient,
                     std::queue<SDL_Event> *text_queue) {
    // TODO assign to class safeQueue a way of being past without pointer
    this->keyboard_input = safeQueueServer;
    this->mouse_input = safeQueueClient;
    this->local_queue = text_queue;
    this->x_move = NONE;
    this->y_move = NONE;
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
        this->mouse_input->push(ib);
        this->keyboard_input->push(ib);
        this->close();
        return;
    }
    std::string eventType;
    std::string actionType;

    switch (e.type){
        case SDL_MOUSEBUTTONDOWN:
            local_queue->push(e);
            eventType = MOUSE_BUTTON_DOWN;
            break;
        case SDL_MOUSEBUTTONUP:
            local_queue->push(e);
            eventType = MOUSE_BUTTON_UP;
            break;
        case SDL_KEYDOWN:
            actionType = ACTION_TYPE;
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    eventType = UP;
                    this->y_move = "UP";
                    break;
                case SDLK_DOWN:
                    eventType = DOWN;
                    this->y_move = "DOWN";
                    break;
                case SDLK_LEFT:
                    eventType = LEFT;
                    this->x_move = "LEFT";
                    break;
                case SDLK_RIGHT:
                    eventType = RIGHT;
                    this->x_move = "RIGHT";
                    break;
                default:
                    return;
            }
        case SDL_KEYUP:
            actionType = ACTION_TYPE_DOWN;
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    if (e.key.state == SDL_RELEASED) this->y_move = NONE;
                    break;
                case SDLK_DOWN:
                    if (e.key.state == SDL_RELEASED) this->y_move = NONE;
                    break;
                case SDLK_LEFT:
                    if (e.key.state == SDL_RELEASED) this->x_move = NONE;
                    break;
                case SDLK_RIGHT:
                    if (e.key.state == SDL_RELEASED) this->x_move = NONE;
                    break;
                default:
                    return;
            }
        default:
            return;
    }

    if( e.type != SDL_KEYDOWN && e.type != SDL_KEYUP) return;

    // For keys
    //Creating infoblock to queue in EventsQueue
    InfoBlock ib;
    ib[actionType] = eventType;
}

void UserInput::close() {
    this->keyboard_input->setOpen(false);
    this->mouse_input->setOpen(false);
    BaseThread::close();
}