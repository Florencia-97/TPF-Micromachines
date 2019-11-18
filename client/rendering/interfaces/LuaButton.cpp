//
// Created by brian on 11/18/19.
//

#include "LuaButton.h"
void LuaButton::render(float screenWidth, float screenHeight) {
    Button::render(screenWidth, screenHeight);
    this->msg.render(screenWidth, screenHeight);
}
LuaButton::LuaButton(SDL_Renderer *sdl_renderer, LTexture *texture) : Button(sdl_renderer, texture) {
    SDL_Color white{255, 255, 255, 0xFF};
    this->msg.init("CLICK FOR USING IA", this->mPosition.x, this->mPosition.y + 100, 27, white, gRenderer);

}
