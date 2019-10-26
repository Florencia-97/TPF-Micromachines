#include <iostream>
#include "yaml-cpp/yaml.h"

#include "../common/Socket.h"
#include "../common/Protocol.h"
#include "../common/constants.h"

int main (int argc, char** argv) {
	Socket socket;
    socket.client(SERVICE ,PORT);
    InfoBlock msg;
    bool success = Protocol::recvMsg(&socket, msg);
    std::cout << msg.srcString() << std::endl;
    std::string yaml = "{x: 2, y: 5}";
    msg.Load(yaml, false);
    Protocol::sendMsg(&socket, msg);
    std::cout << "Client leaves with grace !\n";
}