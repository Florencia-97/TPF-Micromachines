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

  /*Constructor of the Explosion class*/
  Explosion();

  /*Implementation of the inherited function for the creation of the frames
   * PRE: It uses the file client/rendering/assets/decoration/explosion.png*/
  void load_frames(SDL_Renderer *gRenderer) override;

  /*Implementation of the rendering function of an animation frame
   * PRE: x and y are the position values. It starts in the left upper corner
   * (0,0)*/
  void render(int x, int y, SDL_Rect *clip, SDL_Renderer *gRenderer) override;

  /*Implementation of the animation playback function*/
  void play(SDL_Renderer *gRenderer, int x, int y) override;
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_EXPLOSION_H_
