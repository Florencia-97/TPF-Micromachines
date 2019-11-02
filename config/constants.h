#ifndef _CONSTANTS_
#define _CONSTANTS_

#define SERVICE "localhost"
#define PORT "8080"

// First msg
#define ARENA_GAME "GAME_ARENA"
#define CAR_TYPE "CAR_TYPE"


// Selecting race
#define RACE_ID "NUMBER_RACE"

// Game connected
#define CONNECTED_TO_GAME "CONNECTED_TO_GAME"
#define CONNECTED_TO_GAME_NO "NOT_CONNECTED"
#define CONNECTED_TO_GAME_YES "CONNECTED"

// Game owner
#define OWNER "OWNER"
#define OWNER_YES "YES"
#define OWNER_NO "NO"

// Msg starting race!
// race_id already defined
#define MY_ID "MY_ID"
#define PLAYERS_AMOUNT "PLAYERS_AMOUNT"

// Status world
#define OBJECTS_AMOUNT "OBJECTS_AMOUNT"
#define HEALTH "HEALTH"
#define MAX_SPEED "MAX_SPEED"
#define ACELERATION "ACELERATION"
#define ROTATION_MAX "ROTATION_MAX"

// Error tipe
#define GAME_NOT_IN_LOBBY "El juego ya esta siendo jugado, intenta con otro nombre!"

// For messages between server and client
#define ARENA_GAME "GAME_ARENA"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

enum ButtonSprite {
  BUTTON_SPRITE_MOUSE_OUT,
  BUTTON_SPRITE_MOUSE_OVER_MOTION ,
  BUTTON_SPRITE_MOUSE_DOWN,
  BUTTON_SPRITE_MOUSE_UP,
  BUTTON_SPRITE_TOTAL
};

//Button constants
const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 170;
const int TOTAL_BUTTONS = 3;
const int BLUE_CAR_BUTTON_X = 0;
const int BLUE_CAR_BUTTON_Y = 120;
const int BLACK_CAR_BUTTON_X = 320;
const int BLACK_CAR_BUTTON_Y = 120;
const int RED_CAR_BUTTON_X = 1280 / 4 * 3 - 150;
const int RED_CAR_BUTTON_Y = 120;
const int WHITE_CAR_BUTTON_X = 1280 - 150;
const int WHITE_CAR_BUTTON_Y = 120;

const int PLAY_BUTTON_X = 701;
const int PLAY_BUTTON_Y = 600;
const int PLAY_BUTTON_WIDTH = 400;
const int PLAY_BUTTON_HEIGHT = 100;

//MapButtons constants

const int MAP_BUTTON_1_X = 100;
const int MAP_BUTTON_1_Y = 100;
const int MAP_BUTTON_WIDTH = 300;
const int MAP_BUTTON_HEIGHT = 300;

//Car size
const int CAR_WIDTH = 150;
const int CAR_HEIGHT = 170;


// Events
#define ACTION_TYPE "tipe_accion"
#define QUIT "quit"
#define UP "up"
#define DOWN "down"
#define LEFT "left"
#define RIGHT "right"
#define MOUSE_BUTTON_DOWN "button_down"
#define MOUSE_BUTTON_UP "button_up"
#define MOUSE_MOTION "mouse_motion"

#endif
