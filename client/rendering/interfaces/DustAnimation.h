#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_DUSTANIMATION_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_DUSTANIMATION_H_
#include "Animation.h"
class DustAnimation : public Animation {
 private:
 private:
  LTexture texture;
  Uint8 fading;
 public:
  bool isPlaying;
  DustAnimation();
  void load_frames(SDL_Renderer *gRenderer) override;
  void render(int x, int y, SDL_Rect *clip, SDL_Renderer *gRenderer) override;
  void play(SDL_Renderer *gRenderer, int frames, int x, int y) override;
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_DUSTANIMATION_H_
