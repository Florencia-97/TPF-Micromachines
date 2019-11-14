#ifndef MICROMACHINES_FAKECLIENT_H
#define MICROMACHINES_FAKECLIENT_H


#include <queue>
#include "../../common/infostream/InfoBlock.h"

class FakeClient {
    std::queue<InfoBlock>* renderQueue;
    std::queue<InfoBlock>* keyboardQueue;
public:
    FakeClient(std::queue<InfoBlock> &rq, std::queue<InfoBlock> &kq);
    void move();
};


#endif //MICROMACHINES_FAKECLIENT_H
