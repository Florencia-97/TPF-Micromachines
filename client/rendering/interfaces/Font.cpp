//
// Created by brian on 11/2/19.
//

#include "Font.h"

Font::Font(const std::string &msg, SDL_Renderer *renderer) {
  SDL_Color textColor = {0, 0, 0, 0xFF};
  this->font = TTF_OpenFont("../assets/lazy.ttf", 28);
  gInputTextTexture.loadFromRenderedText(msg, textColor, font, renderer);
}
