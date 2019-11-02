//
// Created by brian on 11/2/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_MAPBUTTON_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_MAPBUTTON_H_

#include "Button.h"
class MapButton : public Button {
 public:
  MapButton(SDL_Renderer *sdl_renderer, LTexture *buttonSpriteSheet);
  void set_area(int x, int y) override;

};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_MAPBUTTON_H_
