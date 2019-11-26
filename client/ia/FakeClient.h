#ifndef MICROMACHINES_FAKECLIENT_H
#define MICROMACHINES_FAKECLIENT_H


#include <queue>
#include <string>
#include <common/ThreadQueue.h>
#include "../../common/infostream/InfoBlock.h"
#include "lua/LuaWrapper.h"
#include "../../common/MapsLayer.h"
#include "../../common/conc/BaseThread.h"
#include "../../common/SafeQueue.h"

class FakeClient : public BaseThread {
    SafeQueue<InfoBlock>* keyboardQueue;
    std::queue<InfoBlock>* posQueue;
    ThreadQueue* soundQueue;
    LuaWrapper luaWrapper;
    MapsLayer mapsLayer;
    void _firstMove();
    std::string _getId();
    void _run() override;
    bool _move(InfoBlock& ib, int x, int y, int r, int& lastMove);
public:
    FakeClient(SafeQueue<InfoBlock> &kq, std::queue<InfoBlock> &pos, ThreadQueue *sq);
    void setRace(std::string raceName);
};


#endif //MICROMACHINES_FAKECLIENT_H
