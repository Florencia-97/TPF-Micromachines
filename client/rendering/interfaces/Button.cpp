#include <iostream>
#include <utility>
#include "Button.h"

void Button::setPosition(int x, int y) {
  mPosition.x = x;
  mPosition.y = y;
  set_area(x, y);
}

void Button::changeColor(int r, int g, int b, int duration) {
  this->texture->set_color(r, g, b);
  colorChangeDuration = duration;
}

bool Button::handleEvent(SDL_Event *e, std::queue<std::string> *sq) {
  if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
	//Get mouse position
	int x, y;
	SDL_GetMouseState(&x, &y);
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
	if (inside) {
	  //Set mouse over sprite
	  switch (e->type) {
		case SDL_MOUSEMOTION | SDL_MOUSEBUTTONUP:;
		  return false;
		case SDL_MOUSEBUTTONDOWN:;
		  sq->push(this->soundWhenPressed);
		  callCallbackFunctions();
		  return true;
	  }
	}
  }
  return false;
}
void Button::render(float screenWidth, float screenHeight) {
  if (colorChangeDuration > -1) colorChangeDuration--;
  if (colorChangeDuration == 0) changeColor(255, 255, 255, -1);
  auto widthFactor = float(screenWidth / oldWidth);
  auto heightFactor = float(screenHeight / oldHeight);
  if (widthFactor != 1) {
	this->area.x *= widthFactor;
	this->area.y *= heightFactor;
	this->mPosition.x = this->area.x;
	this->mPosition.y = this->area.y;
	oldWidth = screenWidth;
	oldHeight = screenHeight;
  }
  texture->render_with_size(area.x, area.y, 0, gRenderer,
							area.w, area.h, false);
}

void Button::set_area(int x, int y) {
  this->area = {x, y, BUTTON_WIDTH, BUTTON_HEIGHT};
}

void Button::callCallbackFunctions() {
  for (auto &function : callbacks) {
	function(this->id);
  }
  std::cout << this->id << std::endl;
}

void Button::addCallbackFunction(const std::function<void(std::string)> &cf) {
  callbacks.push_back(cf);
}

Button::Button(std::string id, SDL_Renderer *sdl_renderer,
			   LTexture *buttonSpriteSheet) {
  mPosition.x = 0;
  mPosition.y = 0;
  colorChangeDuration = -1;
  this->texture = buttonSpriteSheet;
  this->gRenderer = sdl_renderer;
  this->id = std::move(id);
  oldWidth = SCREEN_WIDTH;
  oldHeight = SCREEN_HEIGHT;
}


