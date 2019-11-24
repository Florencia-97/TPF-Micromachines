#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_DUSTANIMATION_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_DUSTANIMATION_H_
#include "Animation.h"
class DustAnimation : public Animation {
 private:
 private:
  LTexture texture;
  Uint8 fading;
  bool isPlaying;
 public:

  /*Constructor of the class DustAnimation*/
  DustAnimation();

  /*Implementation of the inherited function for the creation of the frames
 * PRE: It uses the file client/rendering/assets/decoration/Dust.png*/
  void load_frames(SDL_Renderer *gRenderer) override;

  /*Implementation of the rendering function of an animation frame
   PRE: * x and y are the positions in the screen. The parameter clip will not
   be used*/
  void render(int x, int y, SDL_Rect *clip, SDL_Renderer *gRenderer) override;

  /*Implementation of the animation playback function*/
  void play(SDL_Renderer *gRenderer, int frames, int x, int y) override;
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_DUSTANIMATION_H_
