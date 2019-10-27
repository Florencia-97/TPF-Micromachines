//
// Created by brian on 10/26/19.
//

#include "TextureLoader.h"
bool TextureLoader::load_texture(const std::string &path,
                                 LTexture &texture,
                                 SDL_Renderer *renderer) {
  bool success = true;
  if (!texture.load_from_file(path,
                              renderer)) {
    printf("Failed to load dot texture!\n");
    success = false;
  }
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
