#include "Menu.h"
bool Menu::load_media() {
  bool success = true;
  //TODO meter una excepcion por caso;
  carBlue.load_from_file("client/rendering/assets/cars/blue_car.png", gRenderer);
  carBlack.load_from_file("client/rendering/assets/cars/black_car.png", gRenderer);
  carRed.load_from_file("client/rendering/assets/cars/red_car.png", gRenderer);
  carWhite.load_from_file("client/rendering/assets/cars/red_car.png", gRenderer);
  return success;
}

void Menu::init(SDL_Renderer *sdl_renderer) {
  this->gRenderer = sdl_renderer;
  if (!load_media()) {
    printf("Failed to initialize!\n"); //todo exception here
  }
  gButtons.emplace_back(sdl_renderer, &carBlue);
  gButtons.emplace_back(sdl_renderer, &carBlack);
  //Set positions of the three buttons buttons
  gButtons[0].setPosition(BLUE_CAR_BUTTON_X, BLUE_CAR_BUTTON_Y);//Boton asociado al primer vehiculo.
  gButtons[1].setPosition(BLACK_CAR_BUTTON_X, BLACK_CAR_BUTTON_Y);//Boton asociado al segundo vehiculo
  gButtons[2].setPosition(BUTTON_WIDTH * 2, 500);
}

void Menu::render() {
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(gRenderer);
  gButtons[0].render();
  gButtons[1].render();
  gButtons[2].render();

  SDL_RenderPresent(gRenderer);
}


