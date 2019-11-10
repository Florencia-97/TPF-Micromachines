//
// Created by brian on 11/2/19.
//

#include "TextLabel.h"
void TextLabel::init(const std::string &msg, int x, int y, SDL_Color c, SDL_Renderer *sdl_renderer) {
  color = c;
  rate = 0;
  current_frame = 0;
  this->renderText = true;
  renderer = sdl_renderer;
  text = msg;
  this->x = x;
  this->y = y;
  this->font = TTF_OpenFont("client/rendering/interfaces/arcade.ttf", 28);
  textTexture.loadFromRenderedText(text, color, font, sdl_renderer);
  updateBounds();
}
void TextLabel::render() {
  _update();
  if (current_frame == 1) renderText = !renderText;
  if (renderText)
  SDL_RenderCopy(renderer, textTexture.get_texture(), nullptr, &textArea);
}

void TextLabel::updateBounds() {
    this->textArea = {x - textTexture.getWidth()/ 2, y, textTexture.getWidth(),
                      textTexture.getHeight()};
}



void TextLabel::init_intermitent_anim(int rate) {
    this->rate = rate;
}

void TextLabel::stageTextChange(std::string m) {
    this->stagedText.push(m);
}

void TextLabel::stageColorChange(SDL_Color c) {
    this->stagedColors.push(c);
}

void TextLabel::_update() {
    bool needed = false;
    if (!stagedColors.empty()){
        needed = true;
        while (stagedColors.size() > 1) stagedColors.pop();
        color = stagedColors.front();
        stagedColors.pop();
    }
    if (!stagedText.empty()){
        needed = true;
        while (stagedText.size() > 1) stagedText.pop();
        text = stagedText.front();
        stagedText.pop();
    }
    if (rate != 0){
        current_frame = (++current_frame)%rate;
    }
    if (needed) {
        textTexture.free();
        textTexture.loadFromRenderedText(text, color, font, renderer);
    }
}




