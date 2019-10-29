

#include "SenderThread.h"

void SenderThread::_run() {
    bool s = true;
    while (!this->isAlive() && skt->isValid() && to_send.isOpen()){
        InfoBlock send = to_send.pop();
        if (to_send.isOpen())
            s = Protocol::sendMsg(skt, send);
    }
}

void SenderThread::close() {
    if (!this->isAlive()) return;
    to_send.setOpen(false);
    BaseThread::close();
}
