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
  SDL_Rect area;
 public:
  Font(const std::string &msg, SDL_Renderer *renderer);
  void render(SDL_Renderer *p_renderer);

};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_FONT_H_
