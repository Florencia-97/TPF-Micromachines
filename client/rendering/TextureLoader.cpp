#include "TextureLoader.h"
#include "TEXTURE_ERROR.h"

LTexture *TextureLoader::load_texture(std::string name,
									  SDL_Renderer *renderer) {
  if (texture_cache.find(name) == texture_cache.end()) {
	texture_cache.emplace(name, LTexture{});
	if (!texture_cache[name].load_from_file("client/rendering/assets/" + name,
											renderer)) {
	  texture_cache.erase(name);
	  throw TEXTURE_ERROR("error loading image\n");
	}
  }
  return &texture_cache[name];
}