#include <SDL2/SDL_image.h>
#include "LTexture.h"

/*Constructor of LTexture*/
LTexture::LTexture() {
  texture = nullptr;
  width = 0;
  height = 0;
}
/*Destructor of LTexture*/
LTexture::~LTexture() {
  free();
}

/*Loads a texture from the path, using the renderer*/
bool LTexture::load_from_file(const std::string &path,
							  SDL_Renderer *renderer) {
  free();
  SDL_Texture *newTexture = nullptr;
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == nullptr) {
	printf("Unable to load image %s! SDL_image Error: %s\n",
		   path.c_str(), IMG_GetError());
  } else {
	SDL_SetColorKey(loadedSurface,
					SDL_TRUE,
					SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (newTexture == nullptr) {
	  printf("Unable to create texture from %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
	} else {
	  width = loadedSurface->w;
	  height = loadedSurface->h;
	}
	SDL_FreeSurface(loadedSurface);
  }
  texture = newTexture;
  texture_name = path;
  return texture != nullptr;
}

/*Resets the LTexture*/
void LTexture::free() {
  if (texture != nullptr) {
	SDL_DestroyTexture(texture);
	texture = nullptr;
	width = 0;
	height = 0;
  }
}

/* Modules the color in the texture*/
void LTexture::set_color(Uint8 red, Uint8 green, Uint8 blue) {
  SDL_SetTextureColorMod(texture, red, green, blue);
}

void LTexture::render(int x, int y, SDL_Rect *clip, double angle,
					  SDL_Point *center, SDL_RendererFlip flip, SDL_Renderer *renderer) {
  SDL_Rect renderQuad = {x, y, width, height};
  if (clip != nullptr) {
	renderQuad.w = clip->w;
	renderQuad.h = clip->h;
  }
  SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);

}

int LTexture::get_height() {
  return height;
}
int LTexture::get_width() {
  return width;
}

SDL_Texture *LTexture::get_texture() {
  return this->texture;
}
void LTexture::render_with_size(float x, float y, int r, SDL_Renderer *renderer,
								int widthParam, int heightParam, bool id) {
  if (!id) {
	SDL_Rect area = {static_cast<int>(x), static_cast<int>(y),
					 widthParam, heightParam};
	SDL_RenderCopyEx(renderer, texture, nullptr, &area, r,
					 nullptr, SDL_FLIP_NONE);
  } else {
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
  }
}
void LTexture::load_from_rendered_text(const std::string &msg, SDL_Color color,
									   TTF_Font *font, SDL_Renderer *renderer) {
  free();
  //Render text surface
  SDL_Surface *textSurface = TTF_RenderText_Solid(font, msg.c_str(), color);
  if (textSurface != nullptr) {
	//Create texture from surface pixels
	texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (texture == nullptr) {
	  printf("Unable to create texture from rendered text! SDL Error: %s\n",
			 SDL_GetError());
	} else {
	  //Get image dimensions
	  width = textSurface->w;
	  height = textSurface->h;
	}

	//Get rid of old surface
	SDL_FreeSurface(textSurface);
  } else {
	printf("Unable to render text surface! SDL_ttf Error: %s\n",
		   TTF_GetError());
  }
}

void LTexture::set_alpha(Uint8 alpha) {
  //Modulate texture alpha
  SDL_SetTextureAlphaMod(texture, alpha);
}


