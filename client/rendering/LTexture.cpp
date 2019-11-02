#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include "../../config/constants.h"

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
bool LTexture::load_from_file(const std::string &path, SDL_Renderer *renderer) {
  //Primero, hay que limpiar el Texture.
  free();
  //SDL Exige que sea null
  SDL_Texture *newTexture = nullptr;
  //Carga real de la imagen
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == nullptr) {
    //TODO ver si loaded surface tira excepcion
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
  } else {
    //Elige el color que se va a borrar de la imagen. Es decir, setea la capa de color que se va a borrar para que quede png
    SDL_SetColorKey(loadedSurface,
                    SDL_TRUE,
                    SDL_MapRGB(loadedSurface->format,0, 0xFF,0xFF));
    //Textura final

    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    //Todo ver si es necesaria excepcion
    if (newTexture == nullptr) {
      printf("Unable to create texture from %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
    } else {
      width = loadedSurface->w;
      height = loadedSurface->h;
    }
    SDL_FreeSurface(loadedSurface);
  }
  texture = newTexture;
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
void LTexture::set_color(Uint8 red,
                         Uint8 green,
                         Uint8 blue) {
  SDL_SetTextureColorMod(texture,
                         red,
                         green,
                         blue);
}



void LTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center,
                        SDL_RendererFlip flip, SDL_Renderer *renderer) {
  SDL_Rect renderQuad = {x, y, width, height};
  if (clip != nullptr) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }
  SDL_RenderCopyEx(renderer,texture, clip, &renderQuad, angle, center, flip);

}

int LTexture::getHeight() {
  return height;
}
int LTexture::getWidth() {
  return width;
}

SDL_Texture *LTexture::get_texture() {
  return this->texture;
}
void LTexture::render_with_size(int x, int y, int r, SDL_Renderer *renderer, int width, int height) {
  if (x != 0) {
    SDL_Rect area = {x, y, width, height};
    SDL_RenderCopyEx(renderer, texture, nullptr, &area, r, nullptr, SDL_FLIP_NONE);
  } else {
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
  }
}


