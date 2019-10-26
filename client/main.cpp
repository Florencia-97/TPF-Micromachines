#include <iostream>

#include "../common/Socket.h"
#include "../common/Protocol.h"
#include "../common/constants.h"
#include "communication/UserInput.h"
#include "../common/Thread.h"

int main (int argc, char** argv) {
	Socket socket;
    socket.client(SERVICE ,PORT);
    InfoBlock msg;
    bool success = Protocol::recvMsg(&socket, msg);
    std::cout << msg.srcString() << std::endl;
    std::string yaml = "{x: 2, y: 5}";
    msg.Load(yaml, false);
    Protocol::sendMsg(&socket, msg);

    Thread* userInput = new UserInput();
    userInput->start();
    userInput->stop(); //Of course this doesnt goes here
    userInput->join();
    delete(userInput);

    std::cout << "Client leaves with grace !\n";
}