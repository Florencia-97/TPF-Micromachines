

#ifndef MICROMACHINES_GAMERENDERER_H
#define MICROMACHINES_GAMERENDERER_H

#include <SDL2/SDL.h>
#include "SDLStarter.h"
#include <stdexcept>
#include "../GameMap.h"
#include "../Car.h"
#include "TextureLoader.h"
#include <map>
#include "../common/infostream/InfoBlock.h"
#include "../config/constants.h"

class GameRenderer {
    SDL_Rect camera;
    SDL_Renderer *gRenderer;
    TextureLoader tloader;//for map textures

    GameMap map;
    int my_car_id;//position in vector
    Car dumbCar; //todo remove and use the vector
    std::vector<Car> all_cars;

public:

  //the map to render and the car to follow with the camera
  explicit GameRenderer();

  //IMPORTANT
  //PRE gameInfo should have the following keys:
  // [map_name] = std::string to get the config to load the map
  // [my_car_id] = int identificate my car
  // and a list of n cars with their car types (for image loading) and positions
  //TODO GET FROM SERVER

  void init(SDL_Renderer *gr, InfoBlock game_info);

  //pre must be init
  void move_car(int id, int x, int y, float r);

  //pre must be init
  void render();

};


#endif //MICROMACHINES_GAMERENDERER_H
