#ifndef MICROMACHINES_GAMERENDERER_H
#define MICROMACHINES_GAMERENDERER_H

#include <SDL2/SDL.h>
#include "SDLStarter.h"
#include <stdexcept>
#include "../GameMap.h"
#include "../Car.h"
#include "TextureLoader.h"
#include <map>
#include <common/ThreadQueue.h>
#include "../common/infostream/InfoBlock.h"
#include "../config/constants.h"
#include "interfaces/Explosion.h"
#include "interfaces/StainAnimation.h"
#include "interfaces/TextLabel.h"
#include "../Item.h"

class GameRenderer {
  SDL_Rect camera;
  SDL_Renderer *gRenderer;
  TextureLoader tloader;
  Explosion explosion;
  GameMap map;
  std::list<Car> all_cars;
  std::list<Item> all_items;
  StainAnimation stain;
  ThreadQueue *sound_queue;

  TextLabel timer;
  TextLabel health;
  TextLabel laps;
  TextLabel playertag;
  std::list<TextLabel> race_results;

  /*Searchs in the list stored in the object if there is an instance of the
   * object named itemId. If there is, returns true. If not, false*/
  bool _itemInStock(const std::string &itemId);

  /*For each item stored in the vector, delete the oldest instance stored
   * in the object*/
  void _removeOld(std::vector<int> &ids);

  /*Loads all the cars stored, including their positions for later rendering*/
  void load_cars(InfoBlock &inf);

  /*Loads all the items stored, including their positions for later rendering*/
  void load_items(InfoBlock &event);

 public:
  short my_car_id;

  /*Constructor of the class*/
  explicit GameRenderer(ThreadQueue *sq);

  /*Object intializer.
   * PRE: For the correct functioning of the object, it is
   * necessary that this function be executed first */
  void init(SDL_Renderer *gr, InfoBlock &game_info);

  /*Renders the game using the first parameter as a guide.
   * PRE: width and height should be the dimensions of the window*/
  void render(InfoBlock &world_state, int frame, float width, float height);

  /*Updates the player info like health and position and renders them*/
  void update_players(InfoBlock &world_state, int frame);

  /*Leaderboard initializer*/
  void init_leaderboard(InfoBlock &block);
};

#endif //MICROMACHINES_GAMERENDERER_H
