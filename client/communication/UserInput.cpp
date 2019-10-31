#include <SDL2/SDL.h>
#include <iostream>

#include "UserInput.h"
#include "../../config/constants.h"
#include "../common/SafeQueue.h"

UserInput::UserInput(SafeQueue<InfoBlock>* safeQueueServer, SafeQueue<InfoBlock>* safeQueueClient){
    // TODO assign to class safeQueue a way of being past  without pointer
    this->safeQueueServer = safeQueueServer;
    this->safeQueueClient = safeQueueClient;
}

// Why using sdl_WaitEvent? https://stackoverflow.com/questions/18860243/sdl-pollevent-vs-sdl-waitevent
void UserInput::_run(){
    SDL_Event e;
    std::cout << "Starting to read input keys from client\n";
    while (this->isAlive()){
        while( SDL_WaitEvent(&e) != 0 ) {
            _rcvKeyInput(e);
        }
    }
}

void UserInput::_rcvKeyInput(SDL_Event &e){

    if ( e.type == SDL_QUIT){
        this->close();
        return;
    }

    if( e.type != SDL_KEYDOWN) return;

    std::string eventType;
    bool forServer = true;

    switch (e.type){
        // I think we dont care about mouse motion
//        case SDL_MOUSEMOTION:
//            forServer = false;
//            eventType = MOUSE_MOTION;
//            break;
        case SDL_MOUSEBUTTONDOWN:
            forServer = false;
            eventType = MOUSE_BUTTON_DOWN;
            break;
        case SDL_MOUSEBUTTONUP:
            forServer = false;
            eventType = MOUSE_BUTTON_UP;
            break;
    }

    // For keys
    switch (e.key.keysym.sym) {
        case SDLK_UP:
            std::cout << "Key up was pressed!\n";
            eventType = UP;
            break;
        case SDLK_DOWN:
            std::cout << "Key down was pressed!\n";
            eventType = DOWN;
            break;
        case SDLK_LEFT:
            std::cout << "Key left was pressed!\n";
            eventType = LEFT;
            break;
        case SDLK_RIGHT:
            std::cout << "Key right was pressed!\n";
            eventType = RIGHT;
            break;
        default:
            break;
    }
    //Creating infoblock to queue in EventsQueue
    InfoBlock ib;
    ib[ACTION_TYPE] = eventType;
    if (forServer) this->safeQueueServer->push(ib);
    else this->safeQueueClient->push(ib);
}

UserInput::~UserInput() {}