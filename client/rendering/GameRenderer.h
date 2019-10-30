

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
  Car *car;
    TextureLoader tloader;


public:

  //the map to render and the car to follow with the camera
    explicit GameRenderer();

  void init(GameMap *game_map, const std::string &mapConfigPath, Car *p_car);

    void setCamera(int x, int y);

    void render();

    void close();
};


#endif //MICROMACHINES_GAMERENDERER_H
