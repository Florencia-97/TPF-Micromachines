//
// Created by brian on 11/2/19.
//

#include "TextLabel.h"
void TextLabel::init(const std::string &msg, int x, int y, int size, SDL_Color c, SDL_Renderer *sdl_renderer) {
  color = c;
  rate = 0;
  current_frame = 0;
  this->renderText = true;
  renderer = sdl_renderer;
  text = msg;
  this->x = x;
  this->y = y;
  if (!font) this->font = TTF_OpenFont("client/rendering/interfaces/arcade.ttf", size);
  textTexture.loadFromRenderedText(text, color, font, sdl_renderer);
  updateBounds();
  if (!oldWidth) oldWidth = SCREEN_WIDTH;
  if (!oldHeight) oldHeight = SCREEN_HEIGHT;

}
void TextLabel::render(float screenWidth, float screenHeight) {
  _update();
  auto widthFactor = float(screenWidth / oldWidth);
  auto heightFactor = float(screenHeight / oldHeight);
  if (widthFactor != 1) {
    this->textArea.x *= widthFactor;
    this->textArea.y *= heightFactor;
    this->x = this->textArea.x;
    this->y = this->textArea.y;
    oldWidth = screenWidth;
    oldHeight = screenHeight;
  }
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
        updateBounds();
    }
}

TextLabel::TextLabel() {
    oldWidth = 0;
    oldHeight = 0;
    font = nullptr;
}

TextLabel::~TextLabel() {
    textTexture.free();
}




