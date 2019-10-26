#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Tile.h>
#include "SDLStarter.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char *args[]) {
  SDLStarter starter = SDLStarter(SCREEN_HEIGHT, SCREEN_WIDTH, nullptr, nullptr);
  LTexture loader = LTexture();
  //Start up SDL and create window
  if (!starter.init()) {
    printf("Failed to initialize!\n");
  } else {
    Tile *tileSet[1];
    //Load media
    if (!loadMedia(tileSet)) {
      printf("Failed to load media!\n");
    } else {
      //Main loop flag
      bool quit = false;

      //Event handler
      SDL_Event e;

      //The dot that will be moving around on the screen
      Dot dot;

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
          dot.handleEvent(e);
        }

        //Move the dot
        dot.move(tileSet);
        dot.setCamera(camera);

        //Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        //Render level
        for (int i = 0; i < TOTAL_TILES; ++i) {
          tileSet[i]->render(camera);
        }

        //Render dot
        dot.render(camera);

        //Update screen
        SDL_RenderPresent(gRenderer);
      }
    }

    //Free resources and close SDL
    close(tileSet);
  }

  return 0;
}
