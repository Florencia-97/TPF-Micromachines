#include <iostream>
#include <utility>
#include "Button.h"

void Button::set_position(int x, int y) {
  mPosition.x = x;
  mPosition.y = y;
  set_area(x, y);
}

void Button::change_color(int r, int g, int b, int duration) {
  this->texture->set_color(r, g, b);
  colorChangeDuration = duration;
}

bool Button::handle_event(SDL_Event *e, std::queue<std::string> *soundQueue) {
  if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
	//Get mouse position
	int x, y;
	SDL_GetMouseState(&x, &y);
	bool inside = true;
	if (x < mPosition.x || x > mPosition.x + this->area.w) {
	  inside = false;
	} else if (y < mPosition.y || y > mPosition.y + this->area.h) {
	  inside = false;
	}
	if (inside) {
	  //Set mouse over sprite
	  switch (e->type) {
		case SDL_MOUSEMOTION | SDL_MOUSEBUTTONUP:;
		  return false;
		case SDL_MOUSEBUTTONDOWN:;
		  soundQueue->push(this->soundWhenPressed);
		  call_callback_functions();
		  return true;
	  }
	}
  }
  return false;
}

void Button::render(float screenWidth, float screenHeight) {
  if (colorChangeDuration > -1) colorChangeDuration--;
  if (colorChangeDuration == 0) change_color(255, 255, 255, -1);
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

void Button::call_callback_functions() {
  for (auto &function : callbacks) {
	function(this->id);
  }
  std::cout << this->id << std::endl;
}

void Button::add_callback_function(const std::function<void(std::string)> &cf) {
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


