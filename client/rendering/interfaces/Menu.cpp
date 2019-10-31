//
// Created by brian on 10/30/19.
//

#include <vector>
#include "Menu.h"
bool Menu::load_media(std::vector<Button> gButtons) {
  bool success = true;
  if (!gButtonSpriteSheetTexture.load_from_file("button.png", gRenderer)) {
    printf("Failed to load button sprite texture!\n");
    success = false;
  } else {
    //Set sprites. Para ello, particiona la imagen.
    for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) {
      gSpriteClips[i].x = 0;
      gSpriteClips[i].y = i * 200;
      gSpriteClips[i].w = BUTTON_WIDTH;
      gSpriteClips[i].h = BUTTON_HEIGHT;
    }
  }
  this->gButtons = gButtons;
  //Set buttons in corners (HARDCODEADA LA CANTIDAD DE BOTONES)
  gButtons[0].setPosition(0, 0);
  gButtons[1].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, 0);
  gButtons[2].setPosition(0, SCREEN_HEIGHT - BUTTON_HEIGHT);
  gButtons[3].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);
  return success;
}
Menu::Menu(SDL_Renderer *grenderer) {
  this->gRenderer = grenderer;
}

void Menu::start() {/*
  //Start up SDL and create window
  if( !init() ){ //Hay que utilizar el SDLStarter. Hay que manejar tanto el renderer y el window. Se puede crear aca y pasar
    //al siguiente o inicializarlo en el main
    printf( "Failed to initialize!\n" );
  }else{
    //Load media
    std::vector<Button>buttons(4);
    if( !load_media(buttons)){
      printf( "Failed to load media!\n" );
    }else {
      //todo exception
    }
  }
}
 */
  void Menu::render(SDL_Event e) {
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    //Render buttons
    for (int i = 0; i < TOTAL_BUTTONS; ++i) {
      gButtons[i].handleEvent(&e);
    }
    for (int i = 0; i < TOTAL_BUTTONS; ++i) {
      gButtons[i].render();
    }
    //Update screen
    SDL_RenderPresent(gRenderer);
  }



