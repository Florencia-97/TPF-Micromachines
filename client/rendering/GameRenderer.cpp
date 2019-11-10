#include "GameRenderer.h"
#include "../tiles/TilesFactory.h"
#include "../../config/constants.h"
#include "interfaces/StainAnimation.h"

GameRenderer::GameRenderer(){
    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

void GameRenderer::updatePlayers(InfoBlock &world_state, int frame){
    auto my_id = std::to_string(my_car_id);
    for (auto &car: all_cars) {
        car.move(world_state.get<int>("x"+std::to_string(car.id)),
                 world_state.get<int>("y"+std::to_string(car.id)),
                 world_state.get<int>("r"+std::to_string(car.id)));
        if (car.id == my_car_id){
            car.setCamera(camera, map.width, map.height);
        }
        car.render(camera, gRenderer);
    }
    health.stageTextChange( "HP " + world_state.getString("h"+my_id));
    laps.stageTextChange(world_state.getString("l"+my_id) + "   laps");
    timer.stageTextChange(world_state.getString(TIME_LEFT));
}

void GameRenderer::render(InfoBlock &world_state, int frame) {
  map.render(camera, gRenderer);
  updatePlayers(world_state, frame);
  // TODO: We have to load items as they come! (dont really know were that should go)
  for (auto &item: all_items){
      item.render(camera, gRenderer);
  }
  //explosion.play(gRenderer,0,0);
  //stain.play(gRenderer, 0, 0);

  laps.render();
  timer.render();
  health.render();
  SDL_RenderPresent(gRenderer);
}

void GameRenderer::init(SDL_Renderer *gr, InfoBlock &game_info) {
    gRenderer = gr;
    explosion.load_frames(gRenderer);
    stain.load_frames(gRenderer);
    loadCars(game_info);
    map.loadMap("maps/" + game_info.getString(RACE_ID)+".yaml", gRenderer);

    SDL_Color w = {255, 255, 255, 0xFF};

    laps.init("0 LAPS", SCREEN_WIDTH - 100, 25, 35, w, gRenderer);
    timer.init(std::to_string(GAME_DURATION_S), SCREEN_WIDTH / 2, 25, 60, w, gRenderer);
    auto text = "HP " + game_info.getString("h"+std::to_string(my_car_id));
    health.init(text, 100, 25, 35, w, gRenderer);
}

void GameRenderer::loadCars(InfoBlock &cars_info) {
    my_car_id = cars_info.exists(MY_ID) ? cars_info.get<int>(MY_ID) : 0;
    int n_cars = cars_info.exists(PLAYERS_AMOUNT) ? cars_info.get<int>(PLAYERS_AMOUNT) : 1;
    for (int i = 0; i < n_cars; i++) {
        auto id = std::to_string(i);
        this->all_cars.emplace_back(i);
        all_cars.back().move(//set start position and rotation
                cars_info.exists("x" + id) ? cars_info.get<int>("x" + id) : 0,
                cars_info.exists("y" + id) ? cars_info.get<int>("y" + id) : 0,
                cars_info.exists("r" + id) ? cars_info.get<int>("r" + id) : 0);
        
        auto cartype = cars_info.getString(CAR_TYPE+id);
        std::transform(cartype.begin(), cartype.end(), cartype.begin(), ::tolower);
        all_cars.back().addTexture(tloader.load_texture("cars/"+cartype+".png", gRenderer));
    }
}

