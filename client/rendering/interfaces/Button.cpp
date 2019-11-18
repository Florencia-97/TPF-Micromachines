//
// Created by brian on 10/30/19.
//

#include <iostream>
#include "Button.h"
#include "ButtonAnswer.h"

Button::Button(SDL_Renderer *sdl_renderer, LTexture *l_texture) {
  mPosition.x = 0;
  mPosition.y = 0;
  colorChangeDuration = -1;
    this->texture = l_texture;
  this->gRenderer = sdl_renderer;
  this->id = texture->get_string_name();
  this->soundWhenPressed = ""; // no sound
    oldWidth = SCREEN_WIDTH;
    oldHeight = SCREEN_HEIGHT;
}

void Button::setPosition(int x, int y) {
  mPosition.x = x;
  mPosition.y = y;
  set_area(x, y);
}

void Button::changeColor(int r, int g, int b, int duration){
    this->texture->set_color(r, g, b);
    colorChangeDuration = duration;
}

bool Button::handleEvent(SDL_Event *e, std::queue<std::string>* sq) {
  //If mouse event happened

  if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
    //Get mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);

    //Check if mouse is in button
    bool inside = true;

    //Mouse is left of the button
    if (x < mPosition.x) {
      inside = false;
    }
      //Mouse is right of the button
    else if (x > mPosition.x + this->area.w) {
      inside = false;
    }
      //Mouse above the button
    else if (y < mPosition.y) {
      inside = false;
    }
      //Mouse below the button
    else if (y > mPosition.y + this->area.h) {
      inside = false;
    }

    //Mouse is outside button
    if (!inside) {
    }
      //Mouse is inside button
    else {
      //Set mouse over sprite
      switch (e->type) {
        case SDL_MOUSEMOTION:;
          return false;
        case SDL_MOUSEBUTTONDOWN:;
          sq->push(this->soundWhenPressed);
          callCallbackFunctions();
          return true;
        case SDL_MOUSEBUTTONUP:;
          return false;
      }
    }
  }
  return  false;
}
void Button::render(float screenWidth, float screenHeight) {
  if (colorChangeDuration > -1) colorChangeDuration--;
  if (colorChangeDuration == 0) changeColor(255,255,255,-1);
  float widthFactor = float(screenWidth / oldWidth);
  float heightFactor = float(screenHeight / oldHeight);
  if (widthFactor != 1) {
    this->area.x *= widthFactor;
    this->area.y *= heightFactor;
    this->mPosition.x = this->area.x;
    this->mPosition.y = this->area.y;
    oldWidth = screenWidth;
    oldHeight = screenHeight;
  }
  texture->render_with_size(area.x, area.y, 0, gRenderer, area.w, area.h, false);
}

void Button::set_area(int x, int y) {
  this->area = {x, y, BUTTON_WIDTH, BUTTON_HEIGHT};
}

void Button::callCallbackFunctions() {
  for (auto &function : callbacks) {
    function(this->id);
    }
  std::cout<<this->id<<std::endl;
}

void Button::addCallbackFunction(std::function<void(std::string)> cf) {
    callbacks.push_back(cf);
}

std::string Button::getId(){
    return this->id;
}

Button::Button(std::string id, SDL_Renderer *sdl_renderer, LTexture *buttonSpriteSheet) {
    mPosition.x = 0;
    mPosition.y = 0;
    colorChangeDuration = -1;
    this->texture = buttonSpriteSheet;
    this->gRenderer = sdl_renderer;
  this->id = id;
  oldWidth = SCREEN_WIDTH;
  oldHeight = SCREEN_HEIGHT;
}


