
#ifndef MICROMACHINES_CLIENT_H
#define MICROMACHINES_CLIENT_H

#include <client/ia/FakeClient.h>
#include "communication/EventSender.h"
#include "communication/Receiver.h"
#include "communication/UserInput.h"
#include "rendering/TextureLoader.h"
#include "rendering/GameRenderer.h"
#include "GameMap.h"
#include "GameLoop.h"
#include "../config/constants.h"

class serverNotRunning : public std::exception {
  virtual const char *what() const throw() {
	return "Server is not connected, maybe try running it first!\n";
  }
};

class Client {
  Socket skt;
  SafeQueue<InfoBlock> keyboard_e_queue;
  std::queue<SDL_Event> mouse_queue;
  std::queue<SDL_Event> text_queue;
  std::queue<std::string> sound_queue;
  std::queue<std::string> video_queue;
  std::queue<InfoBlock> receiver_queue;
  std::queue<InfoBlock> fake_player_queue;
  std::condition_variable ready_to_connect;
  GameLoop gameLoop;
  UserInput userInput;
  Receiver receiver;
  EventSender sender;
  FakeClient fc;
  std::string port;
  std::string service;
  InfoBlock connection_state;

  /*Attempts to connect to the server. If it was possible, returns true.
   * if not, returns false*/
  bool attempt_connection();

  /*Checks if the state of the connection is equal to CONNECTED_TO_GAME_YES*/
  bool connection_check();
 public:

  /*Constructor of the Client class*/
  Client(std::string &s, std::string &p);

  /*Main function of the object. This starts all the logical processes in the
   * client, like connecting to the server and playing the game.*/
  int play();

  /*Finnish the process of connection to the server and finnish the program*/
  void release();

  /*Waits until the connection to the server is available*/
  bool wait_for_connection();

  /*Waits until the GameLoop is over*/
  void wait_game_end();

  /*Waits until the selection screen is over*/
  void wait_ready_button();

  /*Connects the client to the server. If the connection was successful,
   * then it returns true*/
  bool connect_to_server();

  /* Start all the logical process necessary for sending and receiving messages
   * with the server that make it possible to run the game, therefore, it is
   * necessary that a prior connection has been established*/
  void play_game();
};

#endif //MICROMACHINES_CLIENT_H
