#include <iostream>

#include "../common/stream/InfoBlock.h"
#include "./Talker.h"
#include "../common/stream/Protocol.h"


Talker::Talker(Socket& socket) : skt(std::move(socket)) {}

bool Talker::sendYaml(){
    InfoBlock msg("{race: 1 , players: 5}", false);
    if (!Protocol::sendMsg(&this->skt, msg)) return false;
    bool s = Protocol::recvMsg(&this->skt, msg);
    if (!s) return false;
    std::cout << "x:" << msg.getString("x") << std::endl;
    std::cout << "y:" << msg.getInt("y") << std::endl;
}