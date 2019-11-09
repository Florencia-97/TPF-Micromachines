//
// Created by brian on 11/2/19.
//

#include "ConnectButton.h"
ConnectButton::ConnectButton(SDL_Renderer *sdl_renderer, LTexture *buttonSpriteSheet) : Button(sdl_renderer,
                                                                                               buttonSpriteSheet) {
}
void ConnectButton::set_area(int x, int y) {
  area = {x, y, PLAY_BUTTON_WIDTH, PLAY_BUTTON_HEIGHT};
}

void ConnectButton::render() {
  if (colorChangeDuration > -1) colorChangeDuration--;
  if (colorChangeDuration == 0) changeColor(255, 2, 255, -1);
  SDL_RenderCopy(gRenderer, texture->get_texture(), nullptr, &area);
}
