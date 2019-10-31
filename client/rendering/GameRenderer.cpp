

#include "GameRenderer.h"
#include "../tiles/TilesFactory.h"

GameRenderer::GameRenderer(){
    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

void GameRenderer::render() {
  dumbCar.setCamera(camera);
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(gRenderer);
  map.render(camera, gRenderer);
    dumbCar.render(camera, gRenderer);

  SDL_RenderPresent(gRenderer);
}

void GameRenderer::init(SDL_Renderer *gr, InfoBlock game_info) {
  gRenderer = gr;
  my_car_id = game_info.get<int>("my_car_id");
  dumbCar.addTexture(tloader.load_texture("dot.bmp", gRenderer));

  //todo use vector
  //possible implementation
  //int n = game_info<int>("n_of_cars");
  //for i=0 to n
  //emplace_back(car)
  //vector.back().addTexture(game_info.getString(path+"this_cars_texture_name"));

  map.loadMap("maps/"+game_info.getString("map_name"), gRenderer);
}

void GameRenderer::move_car(int id, int x, int y, float r) {
    dumbCar.move(x, y, r);
}


