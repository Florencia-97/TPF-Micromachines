#include <iostream>
#include "yaml-cpp/yaml.h"

#include "config/Configuration.h"
#include "Talker.h"
#include "../common/Socket.h"
#include "../common/Protocol.h"
#include "../common/constants.h"
#include "GameWorld.h"

int main (int argc, char** argv) {
	Socket socket;
    socket.server(PORT); 
	Socket client = socket.acceptClient();
	Talker talker = Talker(client);
	talker.sendYaml(); //It now contains just an example!
	Configuration config; //Not used yet
}