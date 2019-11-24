#include "GameRenderer.h"
#include "../tiles/TilesFactory.h"
#include "interfaces/StainAnimation.h"
#include <algorithm>

GameRenderer::GameRenderer(std::queue<std::string> &sq) {
  sound_queue = &sq;
  camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  for (int i = 0; i < 6; i++) {
	race_results.emplace_back();
  }
}

void GameRenderer::update_players(InfoBlock &world_state, int frame) {
  auto my_id = std::to_string(my_car_id);
  for (auto &car: all_cars) {
	auto id = std::to_string(car.get_id());
	car.move(world_state.get<int>("x" + id),
			 world_state.get<int>("y" + id),
			 world_state.get<int>("r" + id));
	if (car.get_id() == my_car_id) {
	  car.set_camera(camera, map.width, map.height);
	}
	car.modify_health(world_state.get<int>("h" + id));
	car.render(camera, gRenderer, frame, sound_queue);
  }
  health.stage_text_change("HP " + world_state.getString("h" + my_id));
  laps.stage_text_change("laps  " + world_state.getString("l" + my_id));
  timer.stage_text_change(world_state.getString(TIME_LEFT));
}

void GameRenderer::render(InfoBlock &world_state, int frames,
						  float width, float height) {
  map.render(camera, gRenderer);
  int x = camera.x;
  int y = camera.y;
  load_items(world_state);
  for (auto &item: all_items) {
	item.render(camera, gRenderer);
  }
  update_players(world_state, frames);
  map.renderDeco(camera, gRenderer, camera.x - x, camera.y - y);

  laps.render(width, height);
  timer.render(width, height);
  health.render(width, height);
  playertag.render(width, height);
  for (auto &label : race_results) {
	label.render(width, height);
  }
  auto state = world_state.getString("s" + std::to_string(my_car_id));
  if (state.find("MUD") != std::string::npos) {
	stain.play(gRenderer, frames, 0, 0);
  }
}

void GameRenderer::init(SDL_Renderer *gr, InfoBlock &game_info) {
  gRenderer = gr;
  explosion.load_frames(gRenderer);
  stain.load_frames(gRenderer);
  load_cars(game_info);
  map.loadMap("maps/" + game_info.getString(RACE_ID) + ".yaml", gRenderer);

  SDL_Color w = {255, 255, 255, 0xFF};

  laps.init("0 LAPS", SCREEN_WIDTH - 100, 25, 35, w, gRenderer);
  timer.init(std::to_string(GAME_DURATION_S), SCREEN_WIDTH / 2, 25, 60,
			 w, gRenderer);
  auto text = "HP " + game_info.getString("h" + std::to_string(my_car_id));
  health.init(text, 100, 25, 35, w, gRenderer);
  text = "Player   " + std::to_string(my_car_id);
  playertag.init(text, 100, SCREEN_HEIGHT - 50, 30, w, gRenderer);
  int i = 0;
  for (auto &label : race_results) {
	label.init(" ", 450 + 400 * (i % 2), 350 + 75 * (int) (i / 2), 35,
			   w, gRenderer);
	i++;
  }
}

void GameRenderer::load_cars(InfoBlock &inf) {
  my_car_id = inf.exists(MY_ID) ? inf.get<int>(MY_ID) : 0;
  int n_cars = inf.exists(PLAYERS_AMOUNT) ? inf.get<int>(PLAYERS_AMOUNT) : 1;
  all_cars.clear();
  for (int i = 0; i < n_cars; i++) {
	auto id = std::to_string(i);
	this->all_cars.emplace_back(i);
	all_cars.back().move(
		inf.exists("x" + id) ? inf.get<int>("x" + id) : 0,
		inf.exists("y" + id) ? inf.get<int>("y" + id) : 0,
		inf.exists("r" + id) ? inf.get<int>("r" + id) : 0);

	auto cartype = inf.getString(CAR_TYPE + id);
	std::transform(cartype.begin(), cartype.end(),
				   cartype.begin(), ::tolower);
	all_cars.back().add_texture(tloader.load_texture("cars/" + cartype + ".png",
													 gRenderer));
	all_cars.back().load_animations(gRenderer);
  }
}

bool GameRenderer::_itemInStock(const std::string &itemId) {
  for (auto &item: all_items) {
	if (std::to_string(item.get_id()) == itemId) return true;
  }
  return false;
}

void GameRenderer::load_items(InfoBlock &event) {
  int n_items = event.exists(OBJECTS_AMOUNT) ? event.get<int>(OBJECTS_AMOUNT) : 0;
  std::vector<int> ids;
  for (int i = 0; i < n_items; i++) {
	auto num = std::to_string(i);
	auto itemId = event.getString("OId" + num);
	int itemIdNum = event.getInt("OId" + num);
	ids.push_back(itemIdNum);
	if (_itemInStock(itemId)) continue;
	int x = event.getInt("Ox" + itemId);
	int y = event.getInt("Oy" + itemId);
	int tileNum = event.getInt("Ot" + itemId);
	this->all_items.emplace_back(itemIdNum, x, y);
	all_items.back().addTexture(tloader, gRenderer, tileNum);
  }
  this->_removeOld(ids);
}

void GameRenderer::_removeOld(std::vector<int> &ids) {
  auto it = this->all_items.begin();
  while (it != this->all_items.end()) {
	auto found = std::find(ids.begin(), ids.end(), it->get_id());
	if (found != ids.end()) {
	  ++it;
	} else {
	  it = this->all_items.erase(it);
	}
  }
}

void GameRenderer::init_leaderboard(InfoBlock &block) {
  int i = 0;
  std::string suffix[3] = {"st", "nd", "rd"};
  int n = block.get<int>("SIZE");
  SDL_Color gold{255, 189, 27, 0xFF};

  for (auto &label : race_results) {
	std::string text;
	std::string pos = std::to_string(i + 1) + ((i > 2) ? "th" : suffix[i]);
	if (i < n) {
	  auto id = block.getString("p" + std::to_string(i));
	  auto plr = (id != std::to_string(my_car_id)) ? "Player  " + id : "YOU";
	  text = pos + "     " + plr;
	} else text = pos + "   ";
	label.init(text, 450 + 400 * (i % 2), 350 + 75 * (int) (i / 2), 35,
			   gold, gRenderer);
	i++;
  }
}


