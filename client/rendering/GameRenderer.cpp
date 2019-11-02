

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
  Car car = all_cars.back();
  car.setCamera(camera);
  car.addTexture(tloader.load_texture("cars/black_car.png", gRenderer));
  SDL_RenderClear(gRenderer);
  car.render(camera, gRenderer);
  SDL_RenderPresent(gRenderer);
}

void GameRenderer::init(SDL_Renderer *gr, InfoBlock game_info) {
  gRenderer = gr;
  my_car_id = game_info.get<int>("my_car_id");
  //dumbCar.addTexture(tloader.load_texture("cars/black_car.png", gRenderer));
  InfoBlock ib = InfoBlock("config/tilesInfo.yaml", true);
  load_cars(ib);
  map.loadMap("maps/" + game_info.getString("map_name"), gRenderer);
  int cantidad_de_autos = 1;
  for (int i = 0; i < cantidad_de_autos; i++) {
    this->all_cars.emplace_back();
    all_cars.back().move(0, 0, 0);//todo ver como setear la posicion con el InfoBlock
    all_cars.back().addTexture(tloader.load_texture("cars/black_car.png", gRenderer));
  }
}

void GameRenderer::move_car(short id, int x, int y, float r) {
  for (auto car : all_cars) {
    if (car.compare_id(id)) {
      car.move(x, y, r);
    }
  }
}
void GameRenderer::load_cars(InfoBlock block) {
}

