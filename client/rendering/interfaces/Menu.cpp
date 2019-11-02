#include "Menu.h"
#include "../../../config/constants.h"
#include "CarButton.h"
#include "ConnectButton.h"
bool Menu::load_media() {
  bool success = true;
  //TODO meter una excepcion por caso;
  carBlue.load_from_file("client/rendering/assets/cars/blue_car.png", gRenderer);
  carBlack.load_from_file("client/rendering/assets/cars/black_car.png", gRenderer);
  carRed.load_from_file("client/rendering/assets/cars/red_car.png", gRenderer);
  carWhite.load_from_file("client/rendering/assets/cars/white_car.png", gRenderer);
  wallpaper.load_from_file("client/rendering/assets/all_images/Decor/B.png", gRenderer);
  connectButton.load_from_file("client/rendering/assets/buttons/connect.png", gRenderer);
  return success;
}

void Menu::init(SDL_Renderer *sdl_renderer) {
  this->gRenderer = sdl_renderer;
  if (!load_media()) {
    printf("Failed to initialize!\n"); //todo exception here
  }
  gButtons.push_back(new CarButton(sdl_renderer, &carBlue));
  gButtons.push_back(new CarButton(sdl_renderer, &carWhite));
  gButtons.push_back(new CarButton(sdl_renderer, &carRed));
  gButtons.push_back(new CarButton(sdl_renderer, &carBlack));
  gButtons.emplace_back(new ConnectButton(sdl_renderer, &connectButton));
  //Set positions of the three buttons buttons
  gButtons[0]->setPosition(BLUE_CAR_BUTTON_X, BLUE_CAR_BUTTON_Y);//Boton asociado al primer vehiculo.
  gButtons[1]->setPosition(BLACK_CAR_BUTTON_X, BLACK_CAR_BUTTON_Y);//Boton asociado al segundo vehiculo.
  gButtons[2]->setPosition(RED_CAR_BUTTON_X, RED_CAR_BUTTON_Y);//Boton asociado al tercero.
  gButtons[3]->setPosition(WHITE_CAR_BUTTON_X, WHITE_CAR_BUTTON_Y);//Boton asociado al 4to.
  gButtons[4]->setPosition(PLAY_BUTTON_X, PLAY_BUTTON_Y);
}

void Menu::render() {
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(gRenderer);
  wallpaper.render_with_size(0, 0,0, gRenderer);
  for (auto &button : gButtons) {
    button->render();
  }
  SDL_RenderPresent(gRenderer);
}


