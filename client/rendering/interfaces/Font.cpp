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
  this->areaPromt = {(SCREEN_WIDTH - promptTextTexture.getWidth()) / 2, 0, promptTextTexture.getWidth(),
                     promptTextTexture.getHeight()};
  this->areaInput = {(SCREEN_WIDTH - inputTextTexture.getWidth()) / 2,
                     0,
                     inputTextTexture.getHeight(),
                     inputTextTexture.getHeight()};
}
void Font::render(SDL_Renderer *renderer) {
  SDL_RenderCopy(renderer, promptTextTexture.get_texture(), nullptr, &areaPromt);
  SDL_RenderCopy(renderer, promptTextTexture.get_texture(), nullptr, &areaInput);

}

void Font::receive_input(SDL_Event e) {
  SDL_StartTextInput();
  std::string inputText = "TEAM DRAGON";
  bool renderText = false;
  if (e.type == SDL_KEYDOWN) {
    //Handle backspace
    if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
      //lop off character
      inputText.pop_back();
      renderText = true;
    }
      //Handle copy
    else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
      SDL_SetClipboardText(inputText.c_str());
    }
      //Handle paste
    else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
      inputText = SDL_GetClipboardText();
      renderText = true;
    }
  }
    //Special text input event
  else if (e.type == SDL_TEXTINPUT) {
    //Not copy or pasting
    if (!(SDL_GetModState() & KMOD_CTRL
        && (e.text.text[0] == 'c' || e.text.text[0] == 'C' || e.text.text[0] == 'v' || e.text.text[0] == 'V'))) {
      //Append character
      inputText += e.text.text;
      renderText = true;
    }
  }
  //SI USAMOS ESTA FUNCION, RECORDA UTILIZAR SDL_StopTextInput(); AL MOMENTO DE SACAR ESTO.
}


