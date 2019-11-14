#include "FakeClient.h"

FakeClient::FakeClient(std::queue<InfoBlock> &rq, std::queue<InfoBlock> &kq){
    this->renderQueue = &rq;
    this->keyboardQueue = &kq;
}

void FakeClient::move() {

}