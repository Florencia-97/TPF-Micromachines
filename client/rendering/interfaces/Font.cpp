//
// Created by brian on 11/2/19.
//

#include "Font.h"
Font::Font(const std::string &msg, SDL_Renderer *renderer) {
  SDL_Color textColor = {0, 0, 0, 0xFF};
  this->font = TTF_OpenFont("client/rendering/interfaces/lazy.ttf", 28);
  promptTextTexture.loadFromRenderedText("Inserta el nombre de la partida y elige tu auto!!:",
                                         textColor,
                                         font,
                                         renderer);
  inputTextTexture.loadFromRenderedText(":", textColor, font, renderer);
  this->area = {(SCREEN_WIDTH - promptTextTexture.getWidth()) / 2, 0, promptTextTexture.getWidth(),
                promptTextTexture.getHeight()};
}
void Font::render(SDL_Renderer *renderer) {
  SDL_RenderCopy(renderer, promptTextTexture.get_texture(), nullptr, &area);
}


