//
// Created by brian on 11/9/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_ANIMATION_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_ANIMATION_H_

#include <SDL_rect.h>
#include <SDL_render.h>
#include "../LTexture.h"
class Animation {
 private:
  LTexture actualSprite;
  int frame;
 public:
  virtual void render(int x, int y, SDL_Rect *clip, SDL_Renderer *renderer) = 0;
  virtual void load_frames(SDL_Renderer *gRenderer) = 0;
  virtual void play(SDL_Renderer *gRenderer, int x, int y) = 0;
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_ANIMATION_H_
