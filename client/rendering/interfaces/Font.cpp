//
// Created by brian on 11/2/19.
//

#include "Font.h"

Font::Font(const std::string &path, SDL_Renderer *renderer) {
  SDL_Color textColor = {0, 0, 0, 0xFF};
  gInputTextTexture.loadFromRenderedText(path, textColor, font, renderer);
}
