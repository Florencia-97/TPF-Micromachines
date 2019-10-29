#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include "Tile.h"
#include "SDLStarter.h"
#include "communication/UserInput.h"
#include "MapReader.h"
#include <iostream>
#include "TextureLoader.h"
#include "MapManager.h"
#include "Car.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char *args[]) {
    std::string mapPath = "maps/race_1.yaml";
    MapReader map = MapReader(mapPath);
    std::list<std::list<int>> matrix = map.getMatrix();
    for (auto const& row : matrix) {
        for(auto const& pos : row){
            std::cout << pos << " ";
        }
        std::cout << std::endl;
    }

  /*SDLStarter starter = SDLStarter(SCREEN_HEIGHT,
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
    LTexture carTexture;
    LTexture tiles;
    MapManager manager = MapManager();
    SDL_Renderer *gRenderer = starter.get_global_renderer();
    if (!loader.load_texture("dot.bmp", carTexture, gRenderer) ||
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
        car.move(tileSet, manager);
        car.setCamera(camera);

        //Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        //Render level
        for (int i = 0; i < 192; ++i) {
          tileSet[i]->render(camera, manager.get_tiles_clip(), &tiles);
        }

        //Render dot
        car.render(camera, &carTexture);

        //Update screen
        SDL_RenderPresent(gRenderer);
      }
    }

    //Free resources and close SDL
    carTexture.free();
    starter.close(tileSet);
    tiles.free();
  }
    */
  UserInput in;
  in.run();

  in.join();
  return 0;
}
