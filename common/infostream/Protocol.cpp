#include <string>
#include <iostream>

#include "Protocol.h"
#include "Socket.h"
#include <arpa/inet.h>
#include "InfoBlock.h"

#define LEN_MSG_NOTICE 4

// receives according to protocol:
// * first a uint32_t number to indicate length
// * Second the string with the len given
bool Protocol::recvMsg(Socket* socket, InfoBlock& info){
    try{
        uint32_t len;
        socket->receive(&len, LEN_MSG_NOTICE);
        len = ntohl(len);
        std::string msg(len, '\0');
        socket->receive(&msg[0], (size_t) len);
        info.Load(msg,false);
      auto a = info.srcString();
        return true;
    } catch (socketDisconnected &e){
        std::cout << "Socket disconected\n";
        return false;
    } catch (...){
        std::cerr << "Unknown socket error "<< HERE << std::endl;
    }
}

// send according to protocol:
// * it sends the length of msg (uint32_t)
// * send msg
bool Protocol::sendMsg(Socket* socket, InfoBlock& info){
    std::string msg = info.srcString();
    uint32_t len = htonl(msg.size());
    try {
        socket->sendMsg(&len, LEN_MSG_NOTICE);
        socket->sendMsg(msg.c_str(), msg.size());
    } catch (socketDisconnected &e){
        return false;
    } catch (...){
        std::cerr << "Unknown socket error "<< HERE << std::endl;
    }
    return true;
}