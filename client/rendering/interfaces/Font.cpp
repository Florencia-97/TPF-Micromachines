//
// Created by brian on 11/2/19.
//

#include "Font.h"
void Font::Font_init(const std::string &msg, SDL_Renderer *sdl_renderer) {
  color = {0, 0, 0, 0xFF};
  renderer = sdl_renderer;
  this->font = TTF_OpenFont("client/rendering/interfaces/lazy.ttf", 28);
  promptTextTexture.loadFromRenderedText("Inserta el nombre de la partida y elige tu auto!!!!!!!!!!!!:",
                                         color,
                                         font,
                                         sdl_renderer);
  inputTextTexture.loadFromRenderedText(":", color, font, sdl_renderer);
  this->areaPromt = {(SCREEN_WIDTH - promptTextTexture.getWidth()) / 2, 0, promptTextTexture.getWidth(),
                     promptTextTexture.getHeight()};
  this->areaInput = {(SCREEN_WIDTH - inputTextTexture.getWidth()) / 2,
                     120,
                     inputTextTexture.getWidth(),
                     inputTextTexture.getHeight()};
}
void Font::render() {
  this->areaPromt = {(SCREEN_WIDTH - promptTextTexture.getWidth()) / 2, 0, promptTextTexture.getWidth(),
                     promptTextTexture.getHeight()};
  this->areaInput = {(SCREEN_WIDTH - inputTextTexture.getWidth()) / 2,
                     120,
                     inputTextTexture.getWidth(),
                     inputTextTexture.getHeight()};
  SDL_RenderCopy(renderer, promptTextTexture.get_texture(), nullptr, &areaPromt);
  SDL_RenderCopy(renderer, inputTextTexture.get_texture(), nullptr, &areaInput);

}

void Font::receive_input(SDL_Event *e) {
  SDL_StartTextInput();
  bool renderText = false;
  if (e->type == SDL_KEYDOWN) {
    //Handle backspace
    if (e->key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
      //lop off character
      inputText.pop_back();
      renderText = true;
    }
      //Handle copy
    else if (e->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
      SDL_SetClipboardText(inputText.c_str());
    }
      //Handle paste
    else if (e->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
      inputText = SDL_GetClipboardText();
      renderText = true;
    }
  }
    //Special text input event
  else if (e->type == SDL_TEXTINPUT) {
    //Not copy or pasting
    if (!(SDL_GetModState() & KMOD_CTRL
        && (e->text.text[0] == 'c' || e->text.text[0] == 'C' || e->text.text[0] == 'v' || e->text.text[0] == 'V'))) {
      //Append character
      inputText += e->text.text;
      renderText = true;
    }
  }
  if (renderText) {
    //Text is not empty
    if (!inputText.empty()) {
      //Render new text
      inputTextTexture.loadFromRenderedText(inputText, color, font, renderer);
    } else {
      //Text is empty
      //Render space texture
      inputTextTexture.loadFromRenderedText(" ", color, font, renderer);
    }
  }
}



