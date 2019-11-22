

#include "TextBox.h"

void TextBox::init(const std::string &msg, int x, int y, int size, SDL_Color c, SDL_Renderer *sdl_renderer) {
    TextLabel::init(msg, x, y, size, c, sdl_renderer);
    text = "";
}

void TextBox::receiveInput(SDL_Event *event) {

    bool renderText = false;
  if (event->type == SDL_KEYDOWN) {
        //Handle backspace
	if (event->key.keysym.sym == SDLK_BACKSPACE && text.length() > 0) {
            //lop off character
            text.pop_back();
            renderText = true;
        }
            //Handle copy
	else if (event->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
            SDL_SetClipboardText(text.c_str());
        }
            //Handle paste
	else if (event->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
            text = SDL_GetClipboardText();
            renderText = true;
        }
    }
        //Special text input event
  else if (event->type == SDL_TEXTINPUT) {
        //Not copy or pasting
        if (!(SDL_GetModState() & KMOD_CTRL
			&& (event->text.text[0] == 'c' || event->text.text[0] == 'C' || event->text.text[0] == 'v'
				|| event->text.text[0] == 'V'))) {
            //Append character
		  text += event->text.text;
            renderText = true;
        }
    }
    if (renderText) {
        //Text is not empty
        textTexture.free();
        if (!text.empty()) {
            //Render new text
            textTexture.loadFromRenderedText(text, color, font, renderer);
        } else {
            //Text is empty
            //Render space texture
            textTexture.loadFromRenderedText(" ", color, font, renderer);
        }
    }
}
void TextBox::render(float screenWidth, float screenHeight) {
  _update();
  float widthFactor = screenWidth / oldWidth;
  float heightFactor = screenHeight / oldHeight;
  if (widthFactor != 1 || heightFactor != 1) {
    this->x *= widthFactor;
    this->y *= heightFactor;
    oldWidth = screenWidth;
    oldHeight = screenHeight;
  }
  if (current_frame == 1) renderText = !renderText;
  if (renderText)
    SDL_RenderCopy(renderer, textTexture.get_texture(), nullptr, &textArea);
}
