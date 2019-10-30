#include "rendering/TextureLoader.h"
#include "rendering/GameRenderer.h"
#include "GameMap.h"

int main(int argc, char *args[]) {
  Car car;
  GameMap map;
  GameRenderer gr;
  int x = 0;
  int y = 0;
  gr.init(&map, "maps/race_1.yaml", &car);
  bool quit = false;
  SDL_Event e;
  //While application is running
  while (!quit) {
    //Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
      //User requests quit
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
    gr.move_car(1280 / 2, 960 / 2);
    gr.render();

  }
  gr.close();
  return 0;
}
