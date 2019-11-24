#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_STAINANIMATION_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_STAINANIMATION_H_

#include "Animation.h"
class StainAnimation : public Animation {
 private:
  LTexture texture;
  Uint8 fading;
  bool isPlaying;
 public:

  /*Constructor of the StainAnimation class*/
  StainAnimation();

  /*Implementation of the inherited function for the creation of the frames
 * PRE: It uses the file client/rendering/assets/decoration/stain.png*/
  void load_frames(SDL_Renderer *gRenderer) override;

  /*Implementation of the rendering function of an animation frame
   PRE: * x and y will not be used. The parameter clip will not
   be used*/
  void render(int x, int y, SDL_Rect *clip, SDL_Renderer *renderer) override;

  /*Implementation of the animation playback function
   * PRE: The parameters x and y are not used*/
  void play(SDL_Renderer *gRenderer, int frames, int x, int y) override;

};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_STAINANIMATION_H_
