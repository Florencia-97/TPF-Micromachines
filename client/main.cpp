
#include <iostream>
#include "rendering/SDLStarter.h"
#include <iostream>
#include "rendering/TextureLoader.h"
#include "rendering/GameRenderer.h"
#include "rendering/TEXTURE_ERROR.h"
#include <thread>
#include <chrono>

#include "GameMap.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char *args[]) {

    Car car;
    GameMap map;

    //DOESNT WORK YET BECAUSE THERE IS NO RENDER LOOP, NEEDS TO BE DONE IN RENDERTHREAD

    GameRenderer gr;
    gr.init(&map, "map yaml path which is not used for now", &car);
    gr.render();
    gr.close();

    return 0;
}
