#include "Item.h"
#include "../config/constants.h"

Item::Item(int id, int x, int y){
    mBox.x = x;
    mBox.y = y;
    mBox.w = ITEM_WIDTH;
    mBox.h = ITEM_HEIGHT;
    rotation = 0;
    this->id = id;
}

void Item::render(SDL_Rect &camera, SDL_Renderer *renderer) {
    int x = rand()%2;
    int y = rand()%2;
  texture->render_with_size(mBox.x + x - camera.x,
							mBox.y + y - camera.y,
							rotation,
							renderer,
							ITEM_WIDTH,
							ITEM_HEIGHT,
							false);
  dust.play(renderer, 1, mBox.x + x - camera.x, mBox.y + y - camera.y);
}

void Item::addTexture(TextureLoader& tLoader, SDL_Renderer *gRenderer, int pngNum) {
    std::string nameItem = "speed_boost";
  dust.load_frames(gRenderer);
    switch (pngNum){
        case ITEM_BOOST:
            break;
        case ITEM_ROCK:
            nameItem = "rock";
            break;
        case ITEM_OIL:
            nameItem = "oil";
            break;
        case ITEM_MUD:
            nameItem = "mud";
            break;
        case ITEM_HEALTH:
            nameItem = "health_box";
            break;
        default:
            break;
    }
    this->texture = tLoader.load_texture("modifiers/" + nameItem + ".png", gRenderer);
}
int Item::get_id() {
  return id;
}
