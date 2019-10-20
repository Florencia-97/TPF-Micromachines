#include <iostream>
#include "yaml-cpp/yaml.h"

#include "../common/Socket.h"
#include "../common/Protocol.h"

int main (int argc, char** argv) {
	Socket socket;
    socket.client("localhost" ,"8080"); //remove hardcode
    std::string hola = Protocol::recvMsg(&socket);
    std::cout << hola << std::endl;
    std::cout << "Client leaves with grace !\n";
}