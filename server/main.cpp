#include <iostream>
#include "yaml-cpp/yaml.h"

#include "config/Configuration.h"
#include "Talker.h"
#include "../common/infostream/Socket.h"
#include "../common/constants.h"
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
	    msg = p.event_q.pop();
	    std::cout<<msg.srcString()<<std::endl;
	}
	p.close();
	p.join();
}