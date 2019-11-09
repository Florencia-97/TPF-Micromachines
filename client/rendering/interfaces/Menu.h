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
#include "TextLabel.h"
#include "TextBox.h"
#include <condition_variable>
#include "../TextureLoader.h"

class Menu {
 private:
  LTexture wallpaper;
  TextureLoader textureLoader;
  std::queue<SDL_Event> *mouse_queue;
  std::queue<SDL_Event> *text_queue;
  std::shared_ptr<Button> connectButton;
  SDL_Renderer *gRenderer;

  std::vector<Button> gButtons;
  std::vector<Button> carButtons;
  std::vector<Button> mapButtons;
  std::vector<Button>* active_buttons;

  TextLabel label_choose_car;
  TextBox textbox_lobby_name;

  void load_media();
  void set_buttons_positions();
 public:

  void init(SDL_Renderer *sdl_renderer, std::queue<SDL_Event> *queue, std::queue<SDL_Event> *textQueue);

  void processEventsKeyboard();

  //PRE must be initialized
  void render_first_menu();

  void dummy_init_as_leader();

  void set_buttons_as_leader();

  void init_as_follower();

  bool processEventsMouse(ButtonAnswer &button_answer);

    void setMainMenuMode();
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_MENU_H_
