//
// Created by brian on 11/9/19.
//

#include "StainAnimation.h"
void StainAnimation::render(int x, int y, SDL_Rect *clip, SDL_Renderer *renderer) {
  this->texture->render(x, y, clip, 0, nullptr, SDL_FLIP_NONE, renderer);
}
StainAnimation::StainAnimation() {
  this->fading = 255;
}
void StainAnimation::load_frames(SDL_Renderer *gRenderer) {
  if (!this->texture->load_from_file("client/rendering/assets/decoration/explosion.png", gRenderer)) {
    printf("Failed to load stain texture!\n");
  }
}
void StainAnimation::play(SDL_Renderer *gRenderer, int x, int y) {
  this->texture->setAlpha(fading);
  render(0, 0, nullptr, gRenderer);
  this->fading -= 32;
}


