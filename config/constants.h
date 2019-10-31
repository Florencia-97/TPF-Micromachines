#ifndef _CONSTANTS_
#define _CONSTANTS_

#define SERVICE "localhost"
#define PORT "8080"

// Selecting race
#define NUMBER_RACE "number_race"

// Game connected
#define CONNECTED_TO_GAME "conectado_al_juego"
#define CONNECTED_TO_GAME_YES "OK"
#define CONNECTED_TO_GAME_NO "ERROR"

// Error tipe
#define GAME_NOT_IN_LOBBY "El juego ya esta siendo jugado, intenta con otro nombre!"

// For messages between server and client
#define ARENA_GAME "game_arena"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

// Events
#define ACTION_TYPE "tipo_accion"
#define UP "up"
#define DOWN "down"
#define LEFT "left"
#define RIGHT "right"
#define MOUSE_BUTTON_DOWN "button_down"
#define MOUSE_BUTTON_UP "button_up"
#define MOUSE_MOTION "mouse_motion"

#endif
