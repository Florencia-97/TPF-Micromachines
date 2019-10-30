

#ifndef MICROMACHINES_GAMERENDERER_H
#define MICROMACHINES_GAMERENDERER_H

#include <SDL2/SDL.h>
#include "SDLStarter.h"
#include <stdexcept>
#include "../GameMap.h"
#include "../Car.h"
#include "TextureLoader.h"
#include <map>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class GameRenderer {
    SDL_Rect camera;
    SDL_Renderer *gRenderer;
    SDLStarter starter;
    GameMap* map;
    Car* target;
    TextureLoader tloader;


public:

    //the map to render and the target to follow with the camera
    explicit GameRenderer();

    void init(GameMap *map, std::string mapConfigPath, Car* target);

    void setCamera(int x, int y);

    void render();

    void close();
};


#endif //MICROMACHINES_GAMERENDERER_H
