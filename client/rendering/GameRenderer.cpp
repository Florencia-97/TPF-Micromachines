

#include "GameRenderer.h"
#include "../tiles/TilesFactory.h"

GameRenderer::GameRenderer(): starter(SCREEN_WIDTH, SCREEN_HEIGHT) {
    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

void GameRenderer::render() {
  car->setCamera(camera);

    //Clear screen
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    //Render level
    map->render(camera, gRenderer);
  car->render(camera, gRenderer);

    //Update screen
    SDL_RenderPresent(gRenderer);
}

void GameRenderer::setCamera(int x,int y) {
    //do nothing
}

void GameRenderer::init(GameMap *game_map, std::string mapConfigPath, Car *p_car) {

    if (!starter.init()) {
        throw std::runtime_error("Failed to initialized SDL STARTER");
    }
    gRenderer = starter.get_global_renderer();
  car = p_car;
  p_car->addTexture(tloader.load_texture("dot.bmp", gRenderer));
  this->map = game_map;

  game_map->loadMap(mapConfigPath, gRenderer); //TODO use mapconfig path
    //TilesFactory tilesFactory; // Factory, give a number returns needed Tile
    //tilesFactory.getTile(2, 5, 5, gRenderer); //returns the tile you want
  game_map->dummyInit(5, 5, tloader.load_texture("map/grass.png", gRenderer));
}

void GameRenderer::close(){
    starter.close();
}
