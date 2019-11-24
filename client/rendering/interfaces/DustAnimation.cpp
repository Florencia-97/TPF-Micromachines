#include "../config/constants.h"
#include "DustAnimation.h"
DustAnimation::DustAnimation() {
  this->fading = 255;
  loaded = false;
  isPlaying = true;
}
void DustAnimation::load_frames(SDL_Renderer *gRenderer) {
  if (loaded) return;
  if (!this->texture.load_from_file("assets/decoration/Dust.png",
									gRenderer)) {
	printf("Failed to load stain texture!\n");
  }
  loaded = true;
}
void DustAnimation::render(int x, int y, SDL_Rect *clip, SDL_Renderer *gRenderer) {
  this->texture.render_with_size(x - 50, y - 70, 0.0, gRenderer, ITEM_WIDTH * 3,
								 ITEM_HEIGHT * 3, false);
}

void DustAnimation::play(SDL_Renderer *gRenderer, int frames, int x, int y) {
  if (this->isPlaying) {
	this->texture.set_alpha(fading);
	render(x, y, nullptr, gRenderer);
	this->fading -= 1;
	if (this->fading == 1) {
	  isPlaying = false;
	}
  }
}
