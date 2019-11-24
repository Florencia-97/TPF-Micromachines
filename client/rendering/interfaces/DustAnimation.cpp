#include "DustAnimation.h"
const int ROW = 2;
const int COLUMN = 12;
DustAnimation::DustAnimation() {
  frame = 0;
  loaded = false;
}
void DustAnimation::load_frames(SDL_Renderer *gRenderer) {
  if (loaded) return;
  if (!actualSprite.load_from_file(
	  "assets/decoration/dust.png", gRenderer)) {
	printf("Failed to load explosion texture!\n");
  } else {
	int k = 0;
	for (int i = 0; i < ROW; i++) {
	  for (int j = 0; j < COLUMN; j++) {
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
void DustAnimation::render(int x, int y, SDL_Rect *clip, SDL_Renderer *gRenderer) {
  this->actualSprite.render(x, y, clip, 0, nullptr, SDL_FLIP_NONE, gRenderer);
}
void DustAnimation::play(SDL_Renderer *gRenderer, int frames, int x, int y) {
  SDL_Rect *currentClip = &totalSprites[frame / 10];
  this->render(x, y, currentClip, gRenderer);
  frame = (frame + frames) % TOTAL_FRAMES_DUST;
}
