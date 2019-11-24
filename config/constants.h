#ifndef _CONSTANTS_
#define _CONSTANTS_
#define FPS 40 //client fps
#define GAME_DURATION_S 12 //2mins
#define TIME_LEFT "tl"
#define GAME_END "GG"
#define RACE_RESULTS "RR"

// First msg
#define ARENA_GAME "GA"
#define CAR_TYPE "CT"


// Selecting race
#define RACE_ID "RI"

// Game connected
#define CONNECTED_TO_GAME "CONNECTED_TO_GAME"
#define CONNECTED_TO_GAME_NO "NOT_CONNECTED"
#define CONNECTED_TO_GAME_YES "CONNECTED"

// Game owner
#define OWNER "O"
#define OWNER_YES "Y"
#define OWNER_NO "N"

// Msg starting race!
// race_id already defined
#define MY_ID "MID"
#define PLAYERS_AMOUNT "PAM"

// Status world
#define OBJECTS_AMOUNT "OAM"
#define HEALTH "HE"
#define MAX_SPEED "MS"
#define ACCELERATION "ACC"
#define ROTATION_FORCE "ROT"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

const int BUFFER_WIDTH = 1280, BUFFER_HEIGHT = 960;

const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;


//Button constants
const int BUTTON_WIDTH = 151;
const int BUTTON_HEIGHT = 170;
const int BLUE_CAR_BUTTON_X = 0;
const int BLUE_CAR_BUTTON_Y = 220;
const int BLACK_CAR_BUTTON_X = 320;
const int BLACK_CAR_BUTTON_Y = 220;
const int RED_CAR_BUTTON_X = 1280 / 4 * 3 - 150;
const int RED_CAR_BUTTON_Y = 220;
const int WHITE_CAR_BUTTON_X = 1280 - 150;
const int WHITE_CAR_BUTTON_Y = 220;

const int PLAY_BUTTON_X = 1280 - 200;
const int PLAY_BUTTON_Y = 850;
const int PLAY_BUTTON_WIDTH = 150;
const int PLAY_BUTTON_HEIGHT = 60;


//Car size
const int CAR_WIDTH = 100;
const int CAR_HEIGHT = 170;
#define PTM 20

//Explosion
const int EXPLOSION_FRAMES_ROW = 5;
const int EXPLOSION_FRAMES_COLUMN = 8;
const int TOTAL_FRAMES = EXPLOSION_FRAMES_COLUMN * EXPLOSION_FRAMES_ROW;

// Range between random seed use for item generation
const int TIME_FROM_ITEMS = 5;
const int TIME_TO_ITEMS = 8;
const int MAX_AMOUNT_OBJECTS = 5;

// Items
const int ITEM_HEIGHT = 60;
const int ITEM_WIDTH = 60;
const int ITEMS_AMOUNT = 5;
const int ITEM_BOOST = 0;
const int ITEM_ROCK = 1;
const int ITEM_OIL = 2;
const int ITEM_MUD = 3;
const int ITEM_HEALTH = 4;

// Plugins
const int TIME_BETWEEN_PLUGINS = 15; // seconds

// Events
#define ACTION_TYPE "key"
#define ACTION_TYPE_DOWN "key_up"
#define QUIT 'q'
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define MOUSE_BUTTON_DOWN 'M'
#define MOUSE_BUTTON_UP 'W'

#define MAX_VOLUME_BACKGROUND_SOUND 6
#define MAX_VOLUME_EFFECTS_SOUND 6

#define SOUND_BACKGROUND "SOUND_BACKGROUND"
#define SOUND_ON_OFF "SOUND_ON_OFF"
#define SOUND_CAR_STOP "SOUND_CAR_STOP"
#define SOUND_CAR_STOP_NO "SOUND_CAR_STOP_NO"
#define SOUND_CAR_RUN "SOUND_CAR_RUN"
#define SOUND_STOP_CAR_RUN "SOUND_STOP_CAR_RUN"
#define SOUND_CAR_GEAR "SOUND_CAR_GEAR"
#define VIDEO_RECORDING_ON_OFF "VIDEO_RECORDING_ON_OFF"
#define SOUND_CAR_START "SOUND_CAR_START"
#define SOUND_CAR_HORN "SOUND_CAR_HORN"

#endif
