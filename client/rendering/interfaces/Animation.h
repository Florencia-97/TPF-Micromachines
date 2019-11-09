//
// Created by brian on 11/9/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_ANIMATION_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_ANIMATION_H_
const int EXPLOSION_FRAMES = 4;

#include <SDL_rect.h>
#include "../LTexture.h"
class Animation {
 private:
  LTexture actualSprite;
  SDL_Rect totalSprites[EXPLOSION_FRAMES];
  SDL_Renderer *renderer;
 public:
  Animation(SDL_Renderer *renderer);
  void render(int x, int y, SDL_Rect *clip = nullptr);
  void load_frames();
  void play();
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_ANIMATION_H_
