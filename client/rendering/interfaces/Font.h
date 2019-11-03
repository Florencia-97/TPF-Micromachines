//
// Created by brian on 11/2/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_FONT_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_FONT_H_

#include <SDL_ttf.h>
#include "../LTexture.h"
class Font {
 private:
  TTF_Font *font;
  LTexture gPromptTextTexture;
  LTexture gInputTextTexture;
 public:
  Font(const std::string &msg, SDL_Renderer *renderer);
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_FONT_H_
