//
// Created by brian on 10/30/19.
//

#include <vector>
#include "Menu.h"
bool Menu::load_media() {
    bool success = true;
    if (!gButtonSpriteSheetTexture.load_from_file("client/rendering/assets/buttons/button.png", gRenderer)) {
        printf("Failed to load button sprite texture!\n");
        success = false;
    } else {//todo arreglar que botones se cargan

        for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) {
            gSpriteClips.emplace_back();
            gSpriteClips[i].x = 0;
            gSpriteClips[i].y = i * 200;
            gSpriteClips[i].w = (int)(gButtonSpriteSheetTexture.getWidth()/4);
            gSpriteClips[i].h = (int)(gButtonSpriteSheetTexture.getHeight())/4;
        }
    }
    return success;
}

void Menu::init(SDL_Renderer *gRenderer) {
    this->gRenderer = gRenderer;
    if(!load_media()){
        printf( "Failed to initialize!\n" ); //todo exception here
    }
    for (int i = 0; i < TOTAL_BUTTONS; ++i) {
        gButtons.emplace_back(gRenderer, &gButtonSpriteSheetTexture, &gSpriteClips);
    }

    //Set buttons in corners (HARDCODEADA LA CANTIDAD DE BOTONES)
    gButtons[0].setPosition(0, 0);
    gButtons[1].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, 0);
    gButtons[2].setPosition(0, SCREEN_HEIGHT - BUTTON_HEIGHT);
    gButtons[3].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);
}

void Menu::render() {
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    for (auto button: gButtons) {
      button.render();
    }
    SDL_RenderPresent(gRenderer);
}

Button* Menu::updateButtons(SDL_Event e){
    for (int i = 0; i < TOTAL_BUTTONS; ++i) {
        if (gButtons[i].handleEvent(&e)){
            return &gButtons[i];
        }
    }
    return nullptr;
}


