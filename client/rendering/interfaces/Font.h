//
// Created by brian on 11/2/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_FONT_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_FONT_H_

#include <SDL2/SDL_ttf.h>
#include "../LTexture.h"
#include "../../../config/constants.h"
class Font {
 private:
  TTF_Font *font;
  LTexture promptTextTexture;
  LTexture inputTextTexture;
  SDL_Rect areaPromt;
  SDL_Rect areaInput;
  SDL_Color color;
  SDL_Renderer *renderer;
  std::string inputText = "TEAM DRAGON";
 public:
  void Font_init(const std::string &msg, SDL_Renderer *sdl_renderer);
  void render();
  void receive_input(SDL_Event *e);
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_FONT_H_
