//
// Created by brian on 11/18/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_LUABUTTON_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_LUABUTTON_H_

#include "Button.h"
#include "TextLabel.h"
class LuaButton : public Button {
 private:
  TextLabel msg;
 public:

  LuaButton(SDL_Renderer *sdl_renderer, LTexture *texture);
  void render(float screenWidth, float screenHeight) override;
  void setPosition(int x, int y) override;
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_LUABUTTON_H_
