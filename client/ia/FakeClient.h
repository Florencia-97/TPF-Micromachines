#ifndef MICROMACHINES_FAKECLIENT_H
#define MICROMACHINES_FAKECLIENT_H


#include <queue>
#include "../../common/infostream/InfoBlock.h"
#include "lua/LuaWrapper.h"
#include "../../common/MapsLayer.h"

class FakeClient {
    std::queue<InfoBlock>* renderQueue;
    std::queue<InfoBlock>* keyboardQueue;
    LuaWrapper luaWrapper;
    MapsLayer mapsLayer; // TODO: Check if we can pass an instance of this class
public:
    FakeClient(std::queue<InfoBlock> &rq, std::queue<InfoBlock> &kq, const std::string& map);
    void move();
};


#endif //MICROMACHINES_FAKECLIENT_H
