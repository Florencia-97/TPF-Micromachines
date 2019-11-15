#ifndef MICROMACHINES_FAKECLIENT_H
#define MICROMACHINES_FAKECLIENT_H


#include <queue>
#include "../../common/infostream/InfoBlock.h"
#include "lua/LuaWrapper.h"
#include "../../common/MapsLayer.h"
#include "../../common/conc/BaseThread.h"
#include "../../common/SafeQueue.h"

class FakeClient : public BaseThread {
    //std::queue<InfoBlock>* renderQueue;
    SafeQueue<InfoBlock>* keyboardQueue;
    LuaWrapper luaWrapper;
    MapsLayer mapsLayer; // TODO: Check if we can pass an instance of this class
    void _run() override;
public:
    FakeClient(SafeQueue<InfoBlock> &kq, const std::string& map);
    void move();
};


#endif //MICROMACHINES_FAKECLIENT_H
