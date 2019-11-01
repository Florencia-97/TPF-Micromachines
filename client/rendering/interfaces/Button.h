//
// Created by brian on 10/30/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_H_

#include "../../../config/constants.h"
#include "../LTexture.h"

#include <SDL_events.h>
#include <SDL_system.h>
#include <vector>

class Button {
 private:
  SDL_Renderer *gRenderer = nullptr;
  LTexture *texture;
  SDL_Rect area;

 public:

  //Initializes internal variables
  Button(SDL_Renderer *sdl_renderer, LTexture *buttonSpriteSheet);
  //Sets top left position
  void setPosition(int x, int y);
  //Handles mouse event. If the mouse is clicked, returns true
  bool handleEvent(SDL_Event *e);
  //Shows button sprite
  void render();
  void set_area(int x,
                int y);//todo hay que hacer una funcion que nos deje pasarle las constantes del area del boton a dibujar
 private:
  //Top left position
  SDL_Point mPosition;
  //Currently used global sprite
  ButtonSprite mCurrentSprite;
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_H_
