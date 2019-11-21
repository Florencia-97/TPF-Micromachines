#ifndef _PROTOCOL_
#define _PROTOCOL_

#include <string>
#include "Socket.h"
#include "InfoBlock.h"

class Protocol {
    //Server and client send and recv with same protocol
    public:

    //POS recvs an info block
    //returns true if successfully received
    static bool recvMsg(Socket& socket, InfoBlock& info);

    //POS sends an info block
    //returns true if successfully sent
    static bool sendMsg(Socket& socket, InfoBlock& info);
};

#endif