#include <iostream>
#include <threads/GamesManagerThread.h>

#include "../common/infostream/Socket.h"
#include "../config/constants.h"
#include "threads/GameThread.h"
#include "Game/GameWorld.h"

int main (int argc, char** argv) {

    //example test
	/*Socket socket;
    socket.server(PORT);
	Socket client = socket.acceptClient();
	PlayerThread p(client);
	p.run();
	InfoBlock msg;
	while (p.isRunning() && !msg.exists("exit")){
	    msg = p.eventQ.front();
	    std::cout<<msg.srcString()<<std::endl;
	}
	p.close();
	p.join();*/

	GamesManagerThread* gamesManager = new GamesManagerThread(PORT);
	gamesManager->run();
	std::cout << "Game Manager running!\n";
    std::string input;
    // Server closes with a simple q
    while (input.compare("q") != 0) getline(std::cin, input);
    gamesManager->close();
    gamesManager->join();
    delete(gamesManager);
}