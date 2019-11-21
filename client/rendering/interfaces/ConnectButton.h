#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_CONNECTBUTTON_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_CONNECTBUTTON_H_
#include "Button.h"

class ConnectButton : public Button {
 public:
  /* ConnectButton class constructor */
  ConnectButton(SDL_Renderer *sdl_renderer, LTexture *buttonSpriteSheet);

  /*Overwrites the set_area function of the Button class. In this version,
   * it is modified which constants are used for the calculation*/
  void set_area(int x, int y) override;
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_CONNECTBUTTON_H_
