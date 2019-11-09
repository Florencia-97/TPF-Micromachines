#include "Animation.h"

void Animation::render(int x, int y, SDL_Rect *clip, SDL_Renderer *renderer) {
  this->actualSprite.render(x, y, clip, 0, nullptr, SDL_FLIP_NONE, renderer);
}
void Animation::load_frames(SDL_Renderer *renderer) {
  if (!actualSprite.load_from_file("client/rendering/assets/decoration/explosion.png",
                                   renderer)) {//todo meter esto en el textureLoader
    printf("Failed to load explosion texture!\n");
  } else {
    for (int i = 0; i < EXPLOSION_FRAMES_ROW; i++) {
      for (int j = 0; j < EXPLOSION_FRAMES_COLUMN; j++) {
        totalSprites[i + j].x = 256 * j;
        totalSprites[i + j].y = 0 * i;
        totalSprites[i + j].w = 256;
        totalSprites[i + j].h = 256;
      }
    }
  }
}
void Animation::play(SDL_Renderer *gRenderer, int x, int y) {
  SDL_Rect *currentClip = &totalSprites[frame / 10];
  this->render(x, y, currentClip, gRenderer);
  ++frame;
  if (frame / TOTAL_FRAMES >= TOTAL_FRAMES) {
    frame = 0;
  }
}
Animation::Animation() {
  frame = 0;
}


