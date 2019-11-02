//
// Created by brian on 11/2/19.
//

#include "ConnectButton.h"
ConnectButton::ConnectButton(SDL_Renderer *sdl_renderer, LTexture *buttonSpriteSheet) : Button(sdl_renderer,
                                                                                               buttonSpriteSheet) {
}
void ConnectButton::set_area(int x, int y) {
  area = {x, y, BUTTON_WIDTH, BUTTON_HEIGHT};
}
