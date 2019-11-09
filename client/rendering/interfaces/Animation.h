//
// Created by brian on 11/9/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_ANIMATION_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_ANIMATION_H_
const int EXPLOSION_FRAMES_ROW = 5;
const int EXPLOSION_FRAMES_COLUMN = 8;
const int TOTAL_FRAMES = EXPLOSION_FRAMES_COLUMN * EXPLOSION_FRAMES_ROW;

#include <SDL_rect.h>
#include "../LTexture.h"
class Animation {
 private:
  LTexture actualSprite;
  SDL_Rect totalSprites[TOTAL_FRAMES];
  int frame;

 public:
  Animation();
  void render(int x, int y, SDL_Rect *clip, SDL_Renderer *gRenderer);
  void load_frames(SDL_Renderer *gRenderer);
  void play(SDL_Renderer *gRenderer, int x, int y);
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_ANIMATION_H_
