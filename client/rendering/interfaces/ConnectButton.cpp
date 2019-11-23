#include "ConnectButton.h"
ConnectButton::ConnectButton(SDL_Renderer *sdl_renderer,
							 LTexture *buttonSpriteSheet) :
	Button("connect", sdl_renderer, buttonSpriteSheet) {
  oldWidth = SCREEN_WIDTH;
  oldHeight = SCREEN_HEIGHT;
}
void ConnectButton::set_area(int x, int y) {
  area = {x, y, PLAY_BUTTON_WIDTH, PLAY_BUTTON_HEIGHT};
}
