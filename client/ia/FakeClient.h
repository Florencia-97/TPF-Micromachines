#ifndef MICROMACHINES_FAKECLIENT_H
#define MICROMACHINES_FAKECLIENT_H


#include <queue>
#include "../../common/infostream/InfoBlock.h"
#include "lua/LuaWrapper.h"
#include "../../common/MapsLayer.h"
#include "../../common/conc/BaseThread.h"
#include "../../common/SafeQueue.h"

class FakeClient : public BaseThread {
    SafeQueue<InfoBlock>* keyboardQueue;
    std::queue<InfoBlock>* posQueue;
    LuaWrapper luaWrapper;
    MapsLayer mapsLayer; // TODO: Check if we can pass an instance of this class
    void _run() override;
    void _move(InfoBlock& ib, int x, int y);
public:
    FakeClient(SafeQueue<InfoBlock> &kq, std::queue<InfoBlock> &pos, const std::string& map);
};


#endif //MICROMACHINES_FAKECLIENT_H
