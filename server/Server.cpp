#include <threads/GamesManagerThread.h>
#include "../config/constants.h"

#include "Server.h"


int Server::play() {
    std::cout << "Server running!\n";
    GamesManagerThread gamesManager(PORT);
    gamesManager.run();
    std::cout << "Game Manager running!\n";
    std::string input;
    // Server closes with a simple q
    while (input.compare("q") != 0) getline(std::cin, input);
    gamesManager.close();
    gamesManager.join();
}