#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Tile.h"
#include "SDLStarter.h"
#include "communication/UserInput.h"
#include "MapReader.h"
#include <iostream>
#include "TextureLoader.h"
#include "MapManager.h"
#include "Car.h"
#include "TEXTURE_ERROR.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char *args[]) {
  /*std::string mapPath = "maps/race_1.yaml";
  MapReader map = MapReader(mapPath);
  std::list<std::list<int>> matrix = map.getMatrix();
  for (auto const& row : matrix) {
      for(auto const& pos : row){
          std::cout << pos << " ";
      }
      std::cout << std::endl;
  }
*/
  //Starter se encarga de iniciar SDL
  SDLStarter starter = SDLStarter(SCREEN_WIDTH,
                                  SCREEN_HEIGHT,
                                  nullptr,
                                  nullptr);
  //Start up SDL and create window
  if (!starter.init()) {
    //TODO crear excepcion para esto
    printf("Failed to initialize!\n");
  } else {
    // En total, tendremos 192 casillas individuales.
    Tile *tileSet[192];
    //Load media
    //Texturas que contienen tanto al auto como a todas las tiles como una sola
    LTexture carTexture;
    LTexture tiles;
    //Encargado de manejar colisiones y setear las tiles
    MapManager manager = MapManager();
    //Renderer LINEAL global
    SDL_Renderer *gRenderer = starter.get_global_renderer();
    try {
      //Carga de texturas inicial
      TextureLoader::load_texture("dot.bmp", carTexture, gRenderer);
      TextureLoader::load_texture("tiles.png", tiles, gRenderer);
      manager.setTiles(tileSet, 192);
    }
    catch (TEXTURE_ERROR &error) {
      return 1;
    }

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
        for (auto &element : tileSet) {
          element->render(camera, manager.get_tiles_clip(), &tiles, gRenderer);
        }
        car.render(camera, &carTexture, gRenderer);

        //Update screen
        SDL_RenderPresent(gRenderer);
      }

    //Free resources and close SDL
    carTexture.free();
    starter.close(tileSet);
    tiles.free();
  }
  /*
  UserInput in;
  in.run();

  in.join();*/
  return 0;
}
