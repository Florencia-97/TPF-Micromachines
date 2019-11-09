//
// Created by brian on 11/2/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_CONNECTBUTTON_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_CONNECTBUTTON_H_
#include "Button.h"
class ConnectButton : public Button {
 public:
  ConnectButton(SDL_Renderer *sdl_renderer, LTexture *buttonSpriteSheet);
  void set_area(int x, int y) override;
  void render() override;

};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_CONNECTBUTTON_H_
