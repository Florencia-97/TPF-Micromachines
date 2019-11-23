//
// Created by brian on 10/26/19.
//
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDLStarter.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
extern "C" {
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
}

bool SDLStarter::init() {
  bool success = true;
  av_register_all();
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  } else {
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      printf("Warning: Linear texture filtering not enabled!");
    }
    window = SDL_CreateWindow("Micro Machines: Dragon Series",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              this->screenWidth,
                              this->screenHeight,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    } else {
        icon = IMG_Load("client/rendering/assets/decoration/icon.png");
        SDL_SetWindowIcon(window, icon);
	  renderer = SDL_CreateRenderer(window, -1,
									SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (renderer == nullptr) {
		printf("Renderer could not be created! SDL Error: %s\n",
			   SDL_GetError());

        success = false;
      } else {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
		  printf("SDL_image could not initialize! SDL_image Error: %s\n",
				 IMG_GetError());
          success = false;
        }
        if (TTF_Init() == -1) {
		  printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",
				 TTF_GetError());
          success = false;
        }
        if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
		  printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n",
				 Mix_GetError());
              success = false;
        }
      }
    }
  }
  return success;
}

SDL_Renderer *SDLStarter::get_global_renderer() {
  return renderer;
}

void SDLStarter::close() {
  //Destroy window
  if (icon != nullptr) SDL_FreeSurface(icon);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  window = nullptr;
  renderer = nullptr;

  //Quit SDL subsystems
  Mix_Quit();
  IMG_Quit();
  SDL_Quit();
}

void SDLStarter::get_screen_dimensions(int *width, int *height) {
  SDL_GetWindowSize(window, width, height);
}
