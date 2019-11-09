//
// Created by brian on 11/9/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_STAINANIMATION_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_STAINANIMATION_H_

#include "Animation.h"
class StainAnimation : public Animation {
 private:
  LTexture *texture;
  Uint8 fading;
 public:
  StainAnimation();
  void render(int x, int y, SDL_Rect *clip, SDL_Renderer *renderer) override;
  void load_frames(SDL_Renderer *gRenderer) override;
  void play(SDL_Renderer *gRenderer, int x, int y) override;

};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_STAINANIMATION_H_
