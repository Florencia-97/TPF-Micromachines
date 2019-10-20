
#include "yaml-cpp/yaml.h"
#include "./Talker.h"
#include "../common/Protocol.h"


Talker::Talker(Socket& socket) : skt(std::move(socket)) {}

bool Talker::sendYaml(){
    std::string yaml = "{hola : 4}"; //Example
    int r = Protocol::sendMsg(yaml, &this->skt);
    return r < 0 ? false : true;
}