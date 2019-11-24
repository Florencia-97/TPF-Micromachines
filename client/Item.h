#ifndef MICROMACHINES_ITEM_H
#define MICROMACHINES_ITEM_H

#include <SDL_rect.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <client/rendering/interfaces/DustAnimation.h>
#include "rendering/LTexture.h"
#include "rendering/TextureLoader.h"

class Item {
  SDL_Rect mBox;
  int rotation;
  LTexture *texture;
  int id;
  DustAnimation dust;
 public:

  /*Builder of the class Item.
   * PRE: X and Y are the values ​​of the item's position (following the SDL
   * guidelines)*/
  Item(int id, int x, int y);

  /*Returns the id of the object*/
  int get_id();

  /*Renders the item in the screen using the position of the camera parameter as
   * guide*/
  void render(SDL_Rect &camera, SDL_Renderer *renderer);

  /*Adds a texture to the object in order to show it when the render() method is
   * executed
   * PRE: pngNum must be one of the options for items in constanst.h. These are
   * ITEM_BOOST,ITEM_ROCK,ITEM_MUD,ITEM_OIL or ITEM_HEALTH*/
  void addTexture(TextureLoader &tLoader, SDL_Renderer *renderer, int pngNum);
};

#endif //MICROMACHINES_ITEM_H
