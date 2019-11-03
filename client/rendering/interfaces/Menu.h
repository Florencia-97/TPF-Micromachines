//
// Created by brian on 10/30/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_MENU_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_MENU_H_

#include <SDL_system.h>
#include <queue>
#include "../LTexture.h"
#include "../../../config/constants.h"
#include "Button.h"

class Menu {
 private:
  LTexture carRed;
  LTexture carBlue;
  LTexture carBlack;
  LTexture carWhite;
  LTexture wallpaper;
  std::queue<SDL_Event> *queue;
  LTexture connectButton;
  SDL_Renderer *gRenderer;
  std::vector<Button *> gButtons;
  std::vector<Button *> mapButtons;

  bool load_media();

 public:

    //POS initializes all the components of the menu
    void init(SDL_Renderer *sdl_renderer, std::queue<SDL_Event> *queue);

    //PRE must be initialized
    void render_first_menu(SDL_Event &event);
  void close_first_menu();
  void init_as_leader();

  void init_as_follower();
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_MENU_H_
