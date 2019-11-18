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
    TextLabel playertag;
    std::list<TextLabel> race_results;

    bool _itemInStock(std::string itemId);
    void _removeOld(std::vector<int>& ids);
    void loadCars(InfoBlock& inf);
    void loadItems(InfoBlock &event);
public:

  //the map to render_first_menu and the car to follow with the camera
  explicit GameRenderer();

  void init(SDL_Renderer *gr, InfoBlock &game_info);

  //pre must be init
  void render(InfoBlock &world_state, int frame, float width, float height);

    void updatePlayers(InfoBlock &world_state, int frame);

    short my_car_id;

    void initLeaderboard(InfoBlock &block);
};


#endif //MICROMACHINES_GAMERENDERER_H
