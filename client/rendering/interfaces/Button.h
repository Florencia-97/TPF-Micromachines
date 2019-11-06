//
// Created by brian on 10/30/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_H_

#include "../../../config/constants.h"
#include "../LTexture.h"
#include "Button_answer.h"

#include <SDL_events.h>
#include <SDL_system.h>
#include <vector>

class Button {
 protected:
  SDL_Renderer *gRenderer = nullptr;
  LTexture *texture;
  //Top left position
  SDL_Point mPosition;
  //Currently used global sprite
  ButtonSprite mCurrentSprite;
  SDL_Rect area;
 public:
  Button(SDL_Renderer *sdl_renderer, LTexture *buttonSpriteSheet);
  //Sets top left position
  virtual void setPosition(int x,
                           int y);
  //Handles mouse event. If the mouse is clicked, returns true
  virtual bool handleEvent(SDL_Event *e, Button_answer *answer);
  //Shows button sprite
  virtual void render();
  virtual void set_area(int x,
                int y);
  virtual void free_texture();
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_H_
