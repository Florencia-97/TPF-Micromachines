//
// Created by brian on 11/9/19.
//

#include <zconf.h>
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
  isPlaying = false;
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
  if (!this->isPlaying) isPlaying = true;
  this->texture.set_alpha(fading);
  render(0, 0, nullptr, gRenderer);
  this->fading -= 1 * frames;
  if (this->fading <= 0) {
	fading = 255;
	isPlaying = false;
  }
}


