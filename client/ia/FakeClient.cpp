#include "FakeClient.h"

FakeClient::FakeClient(std::queue<InfoBlock> &rq, std::queue<InfoBlock> &kq, const std::string& mapName):
    luaWrapper(), mapsLayer(mapName) {
    this->renderQueue = &rq;
    this->keyboardQueue = &kq;
}

void FakeClient::move() {
    // Just testing for now
    int x = 3;
    int y = 5;
    // Passing only where he can drive.
    std::string des = luaWrapper.getDesition(mapsLayer.road, x, y);
    std::cout << des << std::endl;
    //Here we will need a sleeo, i guess
}