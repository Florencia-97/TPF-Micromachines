#include "Menu.h"
#include "../../../config/constants.h"
bool Menu::load_media() {
  bool success = true;
  //TODO meter una excepcion por caso;
  carBlue.load_from_file("client/rendering/assets/cars/blue_car.png", gRenderer);
  carBlack.load_from_file("client/rendering/assets/cars/black_car.png", gRenderer);
  carRed.load_from_file("client/rendering/assets/cars/red_car.png", gRenderer);
  carWhite.load_from_file("client/rendering/assets/cars/white_car.png", gRenderer);
  wallpaper.load_from_file("client/rendering/assets/all_images/Decor/B.png", gRenderer);
  return success;
}

void Menu::init(SDL_Renderer *sdl_renderer) {
  this->gRenderer = sdl_renderer;
  if (!load_media()) {
    printf("Failed to initialize!\n"); //todo exception here
  }
  gButtons.emplace_back(sdl_renderer, &carBlue);
  gButtons.emplace_back(sdl_renderer, &carBlack);
  gButtons.emplace_back(sdl_renderer, &carRed);
  gButtons.emplace_back(sdl_renderer, &carWhite);
  //Set positions of the three buttons buttons
  gButtons[0].setPosition(BLUE_CAR_BUTTON_X, BLUE_CAR_BUTTON_Y);//Boton asociado al primer vehiculo.
  gButtons[1].setPosition(BLACK_CAR_BUTTON_X, BLACK_CAR_BUTTON_Y);//Boton asociado al segundo vehiculo.
  gButtons[2].setPosition(RED_CAR_BUTTON_X, RED_CAR_BUTTON_Y);//Boton asociado al tercero.
  gButtons[3].setPosition(WHITE_CAR_BUTTON_X, WHITE_CAR_BUTTON_Y);//Boton asociado al 4to.
}

void Menu::render() {
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(gRenderer);
  wallpaper.render_with_size(0, 0, gRenderer);
  gButtons[0].render();
  gButtons[1].render();
  gButtons[2].render();
  gButtons[3].render();

  SDL_RenderPresent(gRenderer);
}


