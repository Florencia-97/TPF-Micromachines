#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Tile.h"
#include "SDLStarter.h"
#include "communication/UserInput.h"
#include <iostream>
#include "TextureLoader.h"
#include "Car.h"
#include "TEXTURE_ERROR.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char *args[]) {
  SDLStarter starter = SDLStarter(SCREEN_WIDTH, SCREEN_HEIGHT);
  //Start up SDL and create window
  if (!starter.init()) {
      throw std::runtime_error("Failed to initialized SDL STARTER");
  } else {

    //Load media
    LTexture carTexture;
    LTexture tileTexture;
    SDL_Renderer *gRenderer = starter.get_global_renderer();
    try {
      TextureLoader::load_texture("dot.bmp", &carTexture, gRenderer);
      TextureLoader::load_texture("assets/map/grass.png", &tileTexture, gRenderer);
    }
    catch (TEXTURE_ERROR &error) {
      return 1;
    }

      //Main loop flag
      bool quit = false;
      //Event handler TODO move from here
      SDL_Event e;

      //The dot that will be moving around on the screen
      Car car(&carTexture);

      //Level camera
      SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

      //While application is running
      while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
          //User requests quit
          if (e.type == SDL_QUIT) {
            quit = true;
          }

          //Handle input for the dot
          car.handleEvent(e);
        }

        //Move the dot
        //car.move(tileSet, manager);
        car.setCamera(camera);

        //Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        //Render level
        car.render(camera, gRenderer);

        //Update screen
        SDL_RenderPresent(gRenderer);
      }

    //Free resources and close SDL
    starter.close();

  }
  return 0;
}
