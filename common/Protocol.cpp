#include <string>
#include <iostream>

#include "Protocol.h"
#include "Socket.h"
#include <arpa/inet.h>

#define LEN_MSG_NOTICE 4

// receives according to protocol:
// * first a uint32_t number to indicate length
// * Second the string with the len given
std::string Protocol::recvMsg(Socket* socket){
    try{ //Fix this horrible try and carch
        uint32_t len;
        socket->receive(&len, LEN_MSG_NOTICE);
        len = ntohl(len);
        std::string msg(len, '\0');
        socket->receive(&msg[0], (size_t) len);
        return msg;
    } catch (std::exception e){
        return "";
    }
}

// send according to protocol:
// * it sends the length of msg (uint32_t)
// * send msg
int Protocol::sendMsg(std::string& msg, Socket* socket){
    uint32_t len = htonl(msg.size());
    try {
        socket->sendMsg(&len, LEN_MSG_NOTICE);
        socket->sendMsg(msg.c_str(), msg.size());
    } catch(std::exception e){
        return -1;
    }
    return 0;
}