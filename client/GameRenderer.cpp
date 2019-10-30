

#include "GameRenderer.h"

GameRenderer::GameRenderer(): starter(SCREEN_WIDTH, SCREEN_HEIGHT) {
    gRenderer = starter.get_global_renderer();
    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

void GameRenderer::render() {

}

void GameRenderer::setCamera(int x,int y) {

}

void GameRenderer::init() {
    if (!starter.init()) {
        throw std::runtime_error("Failed to initialized SDL STARTER");
    }
}

