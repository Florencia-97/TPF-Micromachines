#include "FakeClient.h"
#include "../../config/constants.h"

FakeClient::FakeClient(SafeQueue<InfoBlock> &kq, std::queue<InfoBlock> &pos, const std::string& mapName):
    luaWrapper(), mapsLayer(mapName) {
    this->keyboardQueue = &kq;
    this->posQueue = &pos;
}

void FakeClient::_run() {
    InfoBlock* gameState;
    while (this->isAlive()){
        // TODO : remove hard coding!
        std::string id = "0";
        //int id = gameState->exists(MY_ID) ? gameState->get<int>(MY_ID) : 0;
        InfoBlock ib;
        if ( !posQueue->empty()){
            InfoBlock ib;
            gameState = &posQueue->front();
            std::cout << gameState->srcString() << std::endl;
            int x = gameState->exists("x" + id) ? gameState->get<int>("x" + id) : 0;
            x = (int) floor(x/TILE_SIZE);
            int y = gameState->exists("y" + id) ? gameState->get<int>("y" + id) : 0;
            y = (int) floor(y/TILE_SIZE);
            std::cout << x << std::endl;
            std::cout << y << std::endl;
            _move(ib, x, y);
            this->keyboardQueue->push(ib);
        }
        this->sleep(0.5);
    }
}

void FakeClient::_move(InfoBlock& ib, int x, int y) {
    // Just testing for now
    // Passing only where he can drive.
    std::string actionType = ACTION_TYPE;
    char eventType;
    ib[actionType] = eventType;
    std::string des = luaWrapper.getDesition(mapsLayer.road, x +1, y+ 1);
    if (des == "UP") eventType = UP;
    else if (des == "DOWN") eventType = DOWN;
    else if (des == "LEFT") eventType = LEFT;
    else eventType = RIGHT;
    ib[actionType] = eventType;
    std::cout << des << std::endl;
}