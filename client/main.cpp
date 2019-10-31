#include "rendering/TextureLoader.h"
#include "rendering/GameRenderer.h"
#include "GameMap.h"
#include "RenderThread.h"

#include <cmath>

int main(int argc, char *args[]) {
  Car car;
  GameMap map;
  GameRenderer gr;
  gr.init(&map, "maps/race_1.yaml", &car);

  std::queue<InfoBlock> event_receiver_queue; //todo
  RenderThread renderThread(gr, event_receiver_queue);
  renderThread.run();

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
    sleep(1/60);
  }

  renderThread.close();
  renderThread.join();
  gr.close();
  return 0;
}
