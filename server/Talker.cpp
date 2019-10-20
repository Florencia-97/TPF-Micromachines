#include <iostream>

#include "yaml-cpp/yaml.h"
#include "./Talker.h"
#include "../common/Protocol.h"


Talker::Talker(Socket& socket) : skt(std::move(socket)) {}

bool Talker::sendYaml(){
    std::string initMsg = "{race: 1 , players: 5}"; //Example sending and receiving to and from server
    if (Protocol::sendMsg(initMsg, &this->skt) < 0) return false;
    std::string position = Protocol::recvMsg(&this->skt);
    if (position == "") return false;
    YAML::Node yaml = YAML::Load(position);
    std::cout << "x:" << yaml["x"].as<std::string>() << std::endl;
    std::cout << "y:" << yaml["y"].as<std::string>() << std::endl;
}