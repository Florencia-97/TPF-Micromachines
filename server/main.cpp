#include <iostream>
#include "yaml-cpp/yaml.h"

#include "config/Configuration.h"
#include "../common/infostream/Socket.h"
#include "../config/constants.h"
#include "threads/GameThread.h"
#include "Game/GameWorld.h"

int main (int argc, char** argv) {
	Socket socket;
    socket.server(PORT);
	Socket client = socket.acceptClient();

	//example test
	PlayerThread p(client);
	p.run();
	InfoBlock msg;
	while (p.isRunning() && !msg.exists("exit")){
	    msg = p.eventQ.front();
	    std::cout<<msg.srcString()<<std::endl;
	}
	p.close();
	p.join();
}