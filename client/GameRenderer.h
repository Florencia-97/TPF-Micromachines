

#ifndef MICROMACHINES_GAMERENDERER_H
#define MICROMACHINES_GAMERENDERER_H

#include <SDL2/SDL.h>
#include "SDLStarter.h"
#include <stdexcept>
#include "GameMap.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class GameRenderer {
    SDL_Rect camera;
    SDL_Renderer *gRenderer;
    SDLStarter starter;
    GameMap* map;


public:

    GameRenderer();

    void init();

    void setCamera(int x, int y);

    void render();
};


#endif //MICROMACHINES_GAMERENDERER_H
