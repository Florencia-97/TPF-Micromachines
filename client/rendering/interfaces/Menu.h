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
#include "Font.h"
#include <condition_variable>

class Menu {
 private:
  LTexture carRed;
  LTexture carBlue;
  LTexture carBlack;
  LTexture carWhite;
  LTexture wallpaper;
  std::queue<SDL_Event> *mouse_queue;
  std::queue<SDL_Event> *text_queue;
  LTexture connectButton;
  SDL_Renderer *gRenderer;
  std::vector<Button *> gButtons;
  std::vector<Button *> mapButtons;
  Font font;

  bool load_media();
  void set_buttons_positions_first_menu();
 public:

    //POS initializes all the components of the menu
    void init(SDL_Renderer *sdl_renderer, std::queue<SDL_Event> *queue, std::queue<SDL_Event> *textQueue);
  void processEventsKeyboard();
  //PRE must be initialized
  void render_first_menu();
  void close_first_menu();
  void dummy_init_as_leader();
  void set_buttons_as_leader();
  void init_as_follower();
  bool processEventsMouse(Button_answer &button_answer);

};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_MENU_H_
