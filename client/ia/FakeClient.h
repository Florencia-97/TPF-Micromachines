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
    // Fake client starts moving foward
    void _firstMove();
    // Gets the id of the car we must control
    std::string _getId();
    // Loop for each we get scripts desition and push it to sender queue
    void _run() override;
    // Gets move of script
    bool _move(InfoBlock& ib, int x, int y, int r, int& lastMove);
public:
    FakeClient(SafeQueue<InfoBlock> &kq, std::queue<InfoBlock> &pos, ThreadQueue *sq);
    // Sets the race we are going to run
    void setRace(std::string raceName);
};


#endif //MICROMACHINES_FAKECLIENT_H
