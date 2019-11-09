//
// Created by brian on 11/9/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_EXPLOSION_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_EXPLOSION_H_

#include <SDL_rect.h>
#include "../LTexture.h"
#include "Animation.h"
#include "../../../config/constants.h"
class Explosion : public Animation {
 private:
  LTexture actualSprite;
  SDL_Rect totalSprites[TOTAL_FRAMES];
  int frame;

 public:
  Explosion();
  void render(int x, int y, SDL_Rect *clip, SDL_Renderer *gRenderer) override;
  void load_frames(SDL_Renderer *gRenderer) override;
  void play(SDL_Renderer *gRenderer, int x, int y) override;
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_EXPLOSION_H_
