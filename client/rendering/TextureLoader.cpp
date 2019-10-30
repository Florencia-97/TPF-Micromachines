//
// Created by brian on 10/26/19.
//

#include "TextureLoader.h"
#include "TEXTURE_ERROR.h"

LTexture* TextureLoader::load_texture(std::string name, SDL_Renderer *renderer) {
    if (texture_cache.find(name) == texture_cache.end()){
        texture_cache.emplace(name, LTexture{});
        if (!texture_cache[name].load_from_file("assets/"+name, renderer)) {
            texture_cache.erase(name);
            throw TEXTURE_ERROR("error loading image\n");
        }
    }
    return &texture_cache[name];
}

void TextureLoader::close(Tile **tiles,
                          int totalTiles,
                          std::vector<LTexture> vector,
                          SDL_Renderer *renderer,
                          SDL_Window *window) {
  //Deallocate tiles
  for (int i = 0; i < totalTiles; ++i) {
    if (tiles[i] == nullptr) {
      delete tiles[i];
      tiles[i] = nullptr;
    }
  }
  for (auto &element : vector) {
    element.free();
  }

  //Destroy window
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  window = nullptr;
  renderer = nullptr;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}
