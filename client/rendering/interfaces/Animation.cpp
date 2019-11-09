//
// Created by brian on 11/9/19.
//

#include "Animation.h"
void Animation::render(int x, int y, SDL_Rect *clip) {
  this->actualSprite.render(x, y, clip, 0, nullptr, SDL_FLIP_NONE, renderer);
}
void Animation::load_frames() {
  if (!actualSprite.load_from_file("decoration/explosion.png", renderer)) {
    printf("Failed to load explosion texture!\n");
  } else {
    //Set sprite clips
    totalSprites[0].x = 0;
    totalSprites[0].y = 0;
    totalSprites[0].w = 64;
    totalSprites[0].h = 205;

    totalSprites[1].x = 64;
    totalSprites[1].y = 0;
    totalSprites[1].w = 64;
    totalSprites[1].h = 205;

    totalSprites[2].x = 128;
    totalSprites[2].y = 0;
    totalSprites[2].w = 64;
    totalSprites[2].h = 205;

    totalSprites[3].x = 196;
    totalSprites[3].y = 0;
    totalSprites[3].w = 64;
    totalSprites[3].h = 205;
  }
}
void Animation::play() {

}
Animation::Animation(SDL_Renderer *renderer) {
  this->renderer = renderer;

}


