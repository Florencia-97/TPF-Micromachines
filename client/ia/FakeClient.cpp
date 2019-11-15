#include "FakeClient.h"
#include "../../config/constants.h"

FakeClient::FakeClient(SafeQueue<InfoBlock> &kq, const std::string& mapName):
    luaWrapper(), mapsLayer(mapName) {
    //this->renderQueue = &rq;
    this->keyboardQueue = &kq;
}

void FakeClient::_run() {
    //move();
    while(this->isAlive()){
        InfoBlock ib;
        std::string actionType = ACTION_TYPE;
        char eventType = UP;
        ib[actionType] = eventType;
        this->keyboardQueue->push(ib);
        this->sleep(1);
    }
}

void FakeClient::move() {
    // Just testing for now
    int x = 3;
    int y = 5;
    // Passing only where he can drive.
    std::string des = luaWrapper.getDesition(mapsLayer.road, x, y);
    std::cout << des << std::endl;
    //Here we will need a sleep, i guess
}