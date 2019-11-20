//
// Created by brian on 11/2/19.
//

#include "ConnectButton.h"
ConnectButton::ConnectButton(SDL_Renderer *sdl_renderer, LTexture *buttonSpriteSheet) : Button("", sdl_renderer,
																																															 buttonSpriteSheet) {
  oldWidth = SCREEN_WIDTH;
  oldHeight = SCREEN_HEIGHT;
}
void ConnectButton::set_area(int x, int y) {
  area = {x, y, PLAY_BUTTON_WIDTH, PLAY_BUTTON_HEIGHT};
}

void ConnectButton::render(float screenWidth, float screenHeight) {
  if (colorChangeDuration > -1) colorChangeDuration--;
  if (colorChangeDuration == 0) changeColor(255, 255, 255, -1);
  float widthFactor = float(screenWidth) / oldWidth;
  float heightFactor = float(screenHeight) / oldHeight;
  if (widthFactor != 1 || heightFactor != 1) {
    this->area.x *= widthFactor;
    this->area.y *= heightFactor;
    this->mPosition.x = this->area.x;
    this->mPosition.y = this->area.y;
    oldWidth = screenWidth;
    oldHeight = screenHeight;
  }
  SDL_RenderCopy(gRenderer, texture->get_texture(), nullptr, &area);
}
