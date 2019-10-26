#include <SDL2/SDL.h>
#include <iostream>

#include "UserInput.h"

UserInput::UserInput(): alive(true) {}

void UserInput::stop() {this->alive = false;}

bool UserInput::isAlive() {return this->alive;}


// Why using sdl_WaitEvent? https://stackoverflow.com/questions/18860243/sdl-pollevent-vs-sdl-waitevent
void UserInput::run(){
    SDL_Event e;
    std::cout << "Starting to read input keys from client\n";
    while (this->alive){
        while( SDL_WaitEvent(&e) != 0 ) {
            _rcvKeyInput(e);
        }
    }
}

void UserInput::_rcvKeyInput(SDL_Event &e){
    if ( e.type == SDL_QUIT){
        this->alive = true;
        return;
    }
    if( e.type != SDL_KEYDOWN) return;

    // It does nothing important right now!
    switch( e.key.keysym.sym ){
        case SDLK_UP:
            std::cout << "Key up was pressed!\n";
            break;

        case SDLK_DOWN:
            std::cout << "Key down was pressed!\n";
            break;

        case SDLK_LEFT:
            std::cout << "Key left was pressed!\n";
            break;

        case SDLK_RIGHT:
            std::cout << "Key right was pressed!\n";
            break;

        default:
            break;
    }
}