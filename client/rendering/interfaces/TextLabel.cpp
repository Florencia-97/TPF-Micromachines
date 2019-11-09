//
// Created by brian on 11/2/19.
//

#include "TextLabel.h"
void TextLabel::init(const std::string &msg, int x, int y, SDL_Color c, SDL_Renderer *sdl_renderer) {
  color = c;
  renderer = sdl_renderer;
  text = msg;
  this->x = x;
  this->y = y;
  this->font = TTF_OpenFont("client/rendering/interfaces/arcade.ttf", 28);
  textTexture.loadFromRenderedText(text, color, font, sdl_renderer);
  updateBounds();
}
void TextLabel::render() {
  SDL_RenderCopy(renderer, textTexture.get_texture(), nullptr, &textArea);
}

void TextLabel::updateBounds() {
    this->textArea = {(x - textTexture.getWidth()) / 2, y, textTexture.getWidth(),
                      textTexture.getHeight()};
}




