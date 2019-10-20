#include <iostream>
#include "yaml-cpp/yaml.h"

#include "../common/Socket.h"
#include "../common/Protocol.h"
#include "../common/constants.h"

int main (int argc, char** argv) {
	Socket socket;
    socket.client(SERVICE ,PORT); //remove hardcode
    std::string hola = Protocol::recvMsg(&socket);
    std::cout << hola << std::endl;
    std::cout << "Client leaves with grace !\n";
}