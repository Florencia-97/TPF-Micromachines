#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Tile.h"
#include "SDLStarter.h"
#include "TextureLoader.h"
#include "MapManager.h"
#include "Car.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char *args[]) {
  SDLStarter starter = SDLStarter(SCREEN_HEIGHT,
                                  SCREEN_WIDTH,
                                  nullptr,
                                  nullptr);
  TextureLoader loader = TextureLoader();
  //Start up SDL and create window
  if (!starter.init()) {
    printf("Failed to initialize!\n");
  } else {
    Tile *tileSet[1];
    //Load media
    LTexture dot;
    LTexture tiles;
    MapManager manager = MapManager();
    SDL_Renderer *gRenderer = starter.get_global_renderer();
    if (!loader.load_texture("dot.bmp", dot, gRenderer) ||
        !loader.load_texture("tiles.png", tiles, gRenderer) ||
        !manager.setTiles(tileSet, 1)) {
      printf("Failed to load media!\n");
    } else {
      //Main loop flag
      bool quit = false;

      //Event handler
      SDL_Event e;

      //The dot that will be moving around on the screen
      Car car;

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
