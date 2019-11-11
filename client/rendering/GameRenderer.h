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
#include "interfaces/Explosion.h"
#include "interfaces/StainAnimation.h"
#include "interfaces/TextLabel.h"
#include "../Item.h"

class GameRenderer {
    SDL_Rect camera;
    SDL_Renderer *gRenderer;
    TextureLoader tloader;//for map textures
    Explosion explosion;
    GameMap map;
    //position in vector
    std::list<Car> all_cars;
    std::list<Item> all_items;
    StainAnimation stain;

    TextLabel timer;
    TextLabel health;
    TextLabel laps;

    bool _itemInStock(std::string itemId);
    void loadCars(InfoBlock& inf);
    void loadItems(InfoBlock &event);
public:

  //the map to render_first_menu and the car to follow with the camera
  explicit GameRenderer();

  void init(SDL_Renderer *gr, InfoBlock &game_info);

  //pre must be init
  void render(InfoBlock &world_state, int frame);

    void updatePlayers(InfoBlock &world_state, int frame);

    short my_car_id;
};


#endif //MICROMACHINES_GAMERENDERER_H
