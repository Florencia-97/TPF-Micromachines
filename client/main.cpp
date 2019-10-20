#include <iostream>
#include "yaml-cpp/yaml.h"

#include "../common/Socket.h"
#include "../common/Protocol.h"
#include "../common/constants.h"

int main (int argc, char** argv) {
	Socket socket;
    socket.client(SERVICE ,PORT);
    std::string initMsg = Protocol::recvMsg(&socket);
    std::cout << initMsg << std::endl;
    std::string yaml = "{x: 2, y: 5}";
    Protocol::sendMsg(yaml, &socket);
    std::cout << "Client leaves with grace !\n";
}