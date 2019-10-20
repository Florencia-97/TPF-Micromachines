#ifndef _PROTOCOL_
#define _PROTOCOL_

#include <string>
#include "Socket.h"

class Protocol {
    //Server and client send and recv with same protocol
    public:
    static std::string recvMsg(Socket* socket);
    static int sendMsg(std::string& msg, Socket* socket);
};

#endif