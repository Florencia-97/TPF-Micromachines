#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_LUABUTTON_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_LUABUTTON_H_

#include "Button.h"
#include "TextLabel.h"
class LuaButton : public Button {
 private:
  TextLabel msg;
 public:

  /*Constructor de la clase LuaButton*/
  LuaButton(SDL_Renderer *sdl_renderer, LTexture *texture);

  /*Implementacion de la funcion para renderizar el boton. El uso de los
   * parametros screenWidth y screenHeight es el mismo que en la clase
   * madre.*/
  void render(float screenWidth, float screenHeight) override;

  /* Implementacion de la funcion setPosition heredada de la clase Button.
   * PRE: Internamente, realiza un llamado a Button::setPosition() para
   * luego establecer la posicion correcta del mensaje asociado al boton.
   * X e Y siguen las mismas condiciones que en la clase madre*/
  void setPosition(int x, int y) override;

  /*Cambia el grado de transparencia del boton.
   * PRE: el rango de i es [0:255] siendo 0 transparente y 255 totalmente
   * opaco*/
  void changeOpacity(int i);
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_LUABUTTON_H_
