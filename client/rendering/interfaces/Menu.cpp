#include "Menu.h"
bool Menu::load_media() {
    bool success = true;
  //TODO meter una excepcion por caso;
  carBlue.load_from_file("client/rendering/assets/cars/blue_car.png", gRenderer);
    if (!gButtonSpriteSheetTexture.load_from_file("client/rendering/assets/buttons/button.png", gRenderer)) {
      printf("Failed to load button sprite texture!\n");
      success = false;
    }
    return success;
}

void Menu::init(SDL_Renderer *sdl_renderer) {
  this->gRenderer = sdl_renderer;
    if(!load_media()){
        printf( "Failed to initialize!\n" ); //todo exception here
    }
    for (int i = 0; i < TOTAL_BUTTONS; ++i) {
      gButtons.emplace_back(sdl_renderer, &carBlue, &gSpriteClips);
    }
  //Set positions of the three buttons buttons
  gButtons[0].setPosition(BLUE_CAR_BUTTON_X, BLUE_CAR_BUTTON_Y);//Boton asociado al primer vehiculo.
  gButtons[1].setPosition(BUTTON_WIDTH, 500);
  gButtons[2].setPosition(BUTTON_WIDTH * 2, 500);
}

void Menu::render() {
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(gRenderer);
  SDL_Rect blueCarBox = {BLUE_CAR_BUTTON_X, BLUE_CAR_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT};
  SDL_RenderCopy(gRenderer, carBlue.get_texture(), nullptr, &blueCarBox);

  SDL_RenderPresent(gRenderer);
}


