#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_ANIMATION_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_ANIMATION_H_

#include <SDL_rect.h>
#include <SDL_render.h>
#include "../LTexture.h"

class Animation {
 private:
	LTexture actualSprite;
	int frame;
 protected:
	bool loaded;
 public:
  /*Loads all animation frames
   * PRE: It must be implemented by the classes that inherit from this*/
	virtual void load_frames(SDL_Renderer *gRenderer) = 0;

  /*Renders an animation frame.
   * PRE: It must be implemented by the classes that inherit from this*/
	virtual void render(int x, int y, SDL_Rect *clip, SDL_Renderer *renderer) = 0;

  /*Plays the animation.
   * PRE: It must be implemented by the classes that inherit from this*/
	virtual void play(SDL_Renderer *gRenderer, int x, int y) = 0;
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_ANIMATION_H_
