

#include "TextBox.h"

void TextBox::init(const std::string &msg, int x, int y, SDL_Color c, SDL_Renderer *sdl_renderer) {
    TextLabel::init(msg, x, y, c, sdl_renderer);
    text = "";
}

void TextBox::receiveInput(SDL_Event *e) {
    SDL_StartTextInput();
    bool renderText = false;
    if (e->type == SDL_KEYDOWN) {
        //Handle backspace
        if (e->key.keysym.sym == SDLK_BACKSPACE && text.length() > 0) {
            //lop off character
            text.pop_back();
            renderText = true;
        }
            //Handle copy
        else if (e->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
            SDL_SetClipboardText(text.c_str());
        }
            //Handle paste
        else if (e->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
            text = SDL_GetClipboardText();
            renderText = true;
        }
    }
        //Special text input event
    else if (e->type == SDL_TEXTINPUT) {
        //Not copy or pasting
        if (!(SDL_GetModState() & KMOD_CTRL
              && (e->text.text[0] == 'c' || e->text.text[0] == 'C' || e->text.text[0] == 'v' || e->text.text[0] == 'V'))) {
            //Append character
            text += e->text.text;
            renderText = true;
        }
    }
    if (renderText) {
        //Text is not empty
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
