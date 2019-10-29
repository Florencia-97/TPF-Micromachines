#include <SDL2/SDL.h>
#include <iostream>

#include "UserInput.h"


// Why using sdl_WaitEvent? https://stackoverflow.com/questions/18860243/sdl-pollevent-vs-sdl-waitevent
void UserInput::_run(){
    SDL_Event e;
    std::cout << "Starting to read input keys from client\n";
    while (this ->isAlive()){
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

    // TODO
    // Might want to see if bitwise actually works
    if (e.key.keysym.sym & (SDLK_UP | SDLK_w)) {
        std::cout << "Key up was pressed!\n";
    } else if (e.key.keysym.sym &(SDLK_DOWN | SDLK_s)) {
        std::cout << "Key down was pressed!\n";
    } else if (e.key.keysym.sym &(SDLK_LEFT | SDLK_a)) {
        std::cout << "Key left was pressed!\n";
    } else if (e.key.keysym.sym &(SDLK_RIGHT | SDLK_d)){
        std::cout << "Key right was pressed!\n";
    }
}