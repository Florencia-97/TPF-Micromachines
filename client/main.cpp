#include "rendering/TextureLoader.h"
#include "rendering/GameRenderer.h"
#include "GameMap.h"
#include "RenderThread.h"


int main(int argc, char *args[]) {
  std::queue<InfoBlock> event_receiver_queue; //todo get from receiver
  RenderThread renderThread(event_receiver_queue);
  renderThread.run();

  sleep(5);
  renderThread.proceedToLobby(true);

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

  return 0;
}
