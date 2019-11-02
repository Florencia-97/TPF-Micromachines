#include "SenderThread.h"

void SenderThread::_run() {
    while (this->isAlive() && skt->isValid() && to_send.isOpen()){
        if (to_send.isOpen()) {
            InfoBlock send = to_send.pop();
            auto a = send.srcString();
            if (!Protocol::sendMsg(skt, send)) break;
        }
    }
}

void SenderThread::close() {
    if (!this->isAlive()) return;
    this->skt->closeSd();
    this->to_send.setOpen(false);
    BaseThread::close();
}
