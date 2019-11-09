//
// Created by brian on 10/30/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_H_

#include "../../../config/constants.h"
#include "../LTexture.h"
#include "ButtonAnswer.h"

#include <SDL_events.h>
#include <SDL_system.h>
#include <list>

class Button {
    void callCallbackFunctions();
 protected:
  SDL_Renderer *gRenderer = nullptr;
  LTexture *texture;
  SDL_Point mPosition;
  ButtonSprite mCurrentSprite;
  SDL_Rect area;

  std::list<void (*)()> callbacks;

 public:

  Button(SDL_Renderer *sdl_renderer, LTexture *buttonSpriteSheet);
  //Sets top left position

  void addCallbackFunction(void (*cf)());

  virtual void setPosition(int x, int y);

  //Handles mouse event. If the mouse is clicked, returns true
  virtual bool handleEvent(SDL_Event *e, ButtonAnswer *answer);
  //Shows button sprite

  virtual void render();

  virtual void set_area(int x, int y);

  virtual void free_texture();
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_H_
