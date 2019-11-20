#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_CONNECTBUTTON_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_CONNECTBUTTON_H_
#include "Button.h"

class ConnectButton : public Button {
 public:
  /*Constructor de la clase ConnectButton*/
  ConnectButton(SDL_Renderer *sdl_renderer, LTexture *buttonSpriteSheet);

  /*Sobreescritura de la funcion set_area de la clase Button. En esta version,
   * se modifica que constantes se usan para el calculo*/
  void set_area(int x, int y) override;
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_CONNECTBUTTON_H_
