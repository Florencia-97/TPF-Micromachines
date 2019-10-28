

#include "SenderThread.h"

void SenderThread::_run() {
    while (!this->isClosed() && skt->isValid() && to_send.isOpen()){
        InfoBlock send = to_send.pop();
        if (to_send.isOpen()) Protocol::sendMsg(skt, send);
    }
}

void SenderThread::close() {
    BaseThread::close();
}
