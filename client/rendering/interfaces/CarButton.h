//
// Created by brian on 11/2/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_CARBUTTON_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_CARBUTTON_H_

#include "Button.h"
class CarButton : public Button {
 public:
  CarButton(SDL_Renderer *sdl_renderer, LTexture *buttonSpriteSheet);
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_CARBUTTON_H_
