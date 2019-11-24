
#include "Client.h"
#include "../common/infostream/Protocol.h"
#include "ia/FakeClient.h"

bool Client::connection_check() {
  return (connection_state.exists(CONNECTED_TO_GAME) &&
	  connection_state.getString(CONNECTED_TO_GAME) == CONNECTED_TO_GAME_YES);
}

void Client::wait_game_end() {
  std::mutex m;
  std::unique_lock<std::mutex> l(m);
  while (!gameLoop.in_menu.load() && !userInput.exit) {
	ready_to_connect.wait(l);
  }
  receiver.close();
  sender.close();
  receiver.join();
  sender.join();
}

void Client::wait_ready_button() {
  gameLoop.menu.ready = false;
  std::mutex m;
  std::unique_lock<std::mutex> l(m);
  while (!gameLoop.menu.ready && !userInput.exit) {
	ready_to_connect.wait(l);
  }
}

bool Client::connect_to_server() {
  skt.client(this->service, this->port);
  if (!skt.isValid()) throw serverNotRunning();
  return true;
}

bool Client::attempt_connection() {
  if (gameLoop.menu.textbox_lobby_name.text.empty()) {
	gameLoop.menu.display_notification("enter  a  lobby  name  to  join  or  create  one!");
	return false;
  }
  connection_state[ARENA_GAME] = gameLoop.menu.textbox_lobby_name.text;
  connection_state[CAR_TYPE] = gameLoop.menu.car_selected;
  if (!Protocol::sendMsg(skt, connection_state)) throw serverNotRunning();
  if (!Protocol::recvMsg(skt, connection_state)) throw serverNotRunning();
  return connection_check();
}

bool Client::wait_for_connection() {
  bool connection_successful = false;
  connect_to_server();
  if (!Protocol::recvMsg(skt, connection_state)) throw serverNotRunning();
  gameLoop.menu.open_games_update.push(connection_state);
  gameLoop.menu.display_notification("open games");
  while (!userInput.exit && !connection_successful) {
	wait_ready_button();
	if (!userInput.exit) {
	  try { connection_successful = attempt_connection(); }
	  catch (serverNotRunning &e) {
		gameLoop.menu.display_notification("cant connect! restart the game");
	  }
	}
  }
}

int Client::play() {
  gameLoop.run();
  userInput.run();
  while (!userInput.exit) {
	try {
	  wait_for_connection();
	} catch (const std::exception &e) {
	  std::cout << e.what() << std::endl;
	  release();
	  return 1;
	}
	play_game();
  }
  release();
  return 0;
}
void Client::play_game() {
  if (skt.isValid() && !userInput.exit) {
	bool is_leader = connection_state.getString(OWNER) == OWNER_YES;
	bool is_ia = gameLoop.menu.get_ia();
	gameLoop.proceedToLobby(is_leader, is_ia);
	if (is_leader) {
	  wait_ready_button();
	  InfoBlock ib;
	  ib[RACE_ID] = gameLoop.menu.map_selected;
	  keyboard_e_queue.push(ib);
	}
	userInput.isScript = is_ia;
	if (is_ia) fc.run();
	if (!receiver.isRunning()) {
	  receiver.run();
	  sender.run();
	}
	wait_game_end();
  }
}

Client::Client(std::string &s, std::string &p) :
	gameLoop(this->receiver_queue, text_queue, mouse_queue, ready_to_connect,
			 sound_queue, fake_player_queue, video_queue),
	userInput(&keyboard_e_queue, &mouse_queue, &text_queue, &sound_queue,
			  &ready_to_connect, &video_queue),
	receiver(skt, &receiver_queue), sender(skt, &keyboard_e_queue),
	fc(this->keyboard_e_queue, this->fake_player_queue) {
  this->service = s;
  this->port = p;
}

void Client::release() {
  skt.closeSd();
  userInput.close();
  sender.close();
  receiver.close();
  gameLoop.close();
  if (fc.isRunning()) {
	fc.close();
	fc.join();
  }
  receiver.join();
  sender.join();
  userInput.join();
  gameLoop.join();
}
