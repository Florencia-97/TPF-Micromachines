#ifndef _TALKER_
#define _TALKER_

#include "../common/infostream/Socket.h"

// Talks to client following protocol, sending yamls
class Talker{
    Socket skt;

    public:
    Talker(Socket& socket);
    bool sendYaml();
};

#endif