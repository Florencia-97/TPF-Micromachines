//
// Created by brian on 10/30/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_MENU_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_MENU_H_

#include <SDL_system.h>
#include "../LTexture.h"
#include "../../../config/constants.h"
#include "Button.h"
class Menu {
 private:
  LTexture gButtonSpriteSheetTexture;
  SDL_Renderer *gRenderer;
  SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
  std::vector<Button> gButtons;
 public:
  Menu(SDL_Renderer *grenderer);
  bool load_media(std::vector<Button> gButtons);
  void start();
  void render(SDL_Event e);
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_MENU_H_
