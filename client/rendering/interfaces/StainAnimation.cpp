
#include <iostream>
#include "StainAnimation.h"
#include "../../../config/constants.h"
void StainAnimation::render(int x, int y, SDL_Rect *clip,
							SDL_Renderer *renderer) {
  this->texture.render_with_size(x, y, 0.0, renderer, SCREEN_WIDTH,
								 SCREEN_HEIGHT, true);
}

StainAnimation::StainAnimation() {
  this->fading = 255;
  loaded = false;
  isPlaying = true;
}

void StainAnimation::load_frames(SDL_Renderer *gRenderer) {
  if (loaded) return;
  if (!this->texture.load_from_file("assets/decoration/stain.png",
									gRenderer)) {
	printf("Failed to load stain texture!\n");
  }
  loaded = true;
}

void StainAnimation::play(SDL_Renderer *gRenderer, int frames, int x, int y) {
  if (isPlaying) {
	this->texture.set_alpha(fading);
	render(0, 0, nullptr, gRenderer);
	Uint8 previous = fading;
	this->fading -= 1 * frames;
	if (fading > previous) {
	  fading = 255;
	  isPlaying = false;
	}
  }
}


