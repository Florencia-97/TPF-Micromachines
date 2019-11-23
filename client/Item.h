#ifndef MICROMACHINES_ITEM_H
#define MICROMACHINES_ITEM_H

#include <SDL_rect.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include "rendering/LTexture.h"
#include "rendering/TextureLoader.h"

class Item {
  SDL_Rect mBox;
  int rotation;
  LTexture *texture;
  int id;
 public:

  Item(int id, int x, int y);
  int get_id();
  void render(SDL_Rect &camera, SDL_Renderer *renderer);
  void addTexture(TextureLoader &tLoader, SDL_Renderer *renderer, int pngNum);
};

#endif //MICROMACHINES_ITEM_H
