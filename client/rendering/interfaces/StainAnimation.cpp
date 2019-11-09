//
// Created by brian on 11/9/19.
//

#include <zconf.h>
#include "StainAnimation.h"
#include "../../../config/constants.h"
void StainAnimation::render(int x, int y, SDL_Rect *clip, SDL_Renderer *renderer) {
  this->texture.render_with_size(x, y, 0.0, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, true);
}

StainAnimation::StainAnimation() {
  this->fading = 255;
}

void StainAnimation::load_frames(SDL_Renderer *gRenderer) {
  if (!this->texture.load_from_file("client/rendering/assets/decoration/stain.png", gRenderer)) {
    printf("Failed to load stain texture!\n");
  }
}
void StainAnimation::play(SDL_Renderer *gRenderer, int x, int y) {
  this->texture.setAlpha(fading);
  render(0, 0, nullptr, gRenderer);
  this->fading -= 1;
  if (this->fading <= 0) {
    fading = 255;
  }
}


