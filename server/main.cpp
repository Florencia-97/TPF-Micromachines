#include <iostream>
#include "yaml-cpp/yaml.h"

#include "config/Configuration.h"
#include "Talker.h"
#include "../common/Socket.h"
#include "../common/Protocol.h"
#include "../common/constants.h"

int main (int argc, char** argv) {
	Socket socket;
    socket.server(PORT); // remove harcoded after
	Socket client = socket.acceptClient();
	Talker talker = Talker(client);
	talker.sendYaml();
	Configuration config; //Not used yet
}