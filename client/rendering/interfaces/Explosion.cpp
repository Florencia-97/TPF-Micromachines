#include <iostream>
#include "Explosion.h"

void Explosion::render(int x, int y, SDL_Rect *clip, SDL_Renderer *renderer) {
  this->actualSprite.render(x, y, clip, 0, nullptr, SDL_FLIP_NONE, renderer);
}
void Explosion::load_frames(SDL_Renderer *renderer) {
    if (loaded) return;
  if (!actualSprite.load_from_file(
	  "client/rendering/assets/decoration/explosion.png", renderer)) {
    printf("Failed to load explosion texture!\n");
  } else {
    int k = 0;
    for (int i = 0; i < EXPLOSION_FRAMES_ROW; i++) {
      for (int j = 0; j < EXPLOSION_FRAMES_COLUMN; j++) {
        totalSprites[k].x = 256 * j;
        totalSprites[k].y = 256 * i;
        totalSprites[k].w = 256;
        totalSprites[k].h = 256;
        k++;
      }
    }
  }
  loaded = true;
}
void Explosion::play(SDL_Renderer *gRenderer, int frames, int x, int y) {
  SDL_Rect *currentClip = &totalSprites[frame / 10];
  this->render(x, y, currentClip, gRenderer);
  frame =  (frame + frames)%TOTAL_FRAMES;

}
Explosion::Explosion() {
  frame = 0;
  loaded = false;
}


