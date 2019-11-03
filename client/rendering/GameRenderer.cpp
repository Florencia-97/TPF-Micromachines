

#include "GameRenderer.h"
#include "../tiles/TilesFactory.h"
#include "../../config/constants.h"

GameRenderer::GameRenderer(){
    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

void GameRenderer::render() {
  dumbCar.setCamera(camera);
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(gRenderer);
  map.render(camera, gRenderer);
  for (auto &car: all_cars){
      //car.setCamera(camera);
      car.render(camera, gRenderer);
  }
  SDL_RenderPresent(gRenderer);
}

void GameRenderer::init(SDL_Renderer *gr, InfoBlock game_info) {
    gRenderer = gr;
    loadCars(game_info);
    map.loadMap("maps/" + game_info.getString(RACE_ID)+".yaml", gRenderer);
}

void GameRenderer::move_car(short id, int x, int y, float r) {
  for (auto car : all_cars) {
    if (car.compare_id(id)) {
      car.move(x, y, r);
    }
  }
}

void GameRenderer::loadCars(InfoBlock &cars_info) {
    my_car_id = cars_info.exists(MY_ID) ? cars_info.get<int>(MY_ID) : 0;
    int n_cars = cars_info.exists(PLAYERS_AMOUNT) ? cars_info.get<int>(PLAYERS_AMOUNT) : 1;
    //auto a = cars_info.srcString();
    for (int i = 0; i < n_cars; i++) {
        auto id = std::to_string(i);
        this->all_cars.emplace_back();
        all_cars.back().move(//set start position and rotation
                cars_info.exists("x" + id) ? cars_info.get<int>("x" + id) : 0,
                cars_info.exists("y" + id) ? cars_info.get<int>("y" + id) : 0,
                cars_info.exists("r" + id) ? cars_info.get<int>("r" + id) : 0);
        all_cars.back().addTexture(tloader.load_texture("cars/blue_car.png", gRenderer));
    }
}

