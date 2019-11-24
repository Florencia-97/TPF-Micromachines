#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_DUSTANIMATION_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_DUSTANIMATION_H_

const int TOTAL_FRAMES_DUST = 13;
#include "Animation.h"
class DustAnimation : public Animation {
 private:
 private:
  LTexture actualSprite;
  SDL_Rect totalSprites[TOTAL_FRAMES_DUST];
  int frame;
 public:
  DustAnimation();
  void load_frames(SDL_Renderer *gRenderer) override;
  void render(int x, int y, SDL_Rect *clip, SDL_Renderer *gRenderer) override;
  void play(SDL_Renderer *gRenderer, int frames, int x, int y) override;
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_DUSTANIMATION_H_
