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
  std::vector<SDL_Rect> gSpriteClips;
  std::vector<Button> gButtons;

 public:

  bool load_media();

  void init(SDL_Renderer *gRenderer);

  void render();

  //POS checks for events and updates button based on the event
  //returns a pointer to the updated button or a nullptr if no button
  //events were registered
  Button* updateButtons(SDL_Event e);
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_MENU_H_
