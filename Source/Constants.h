//
// Created by haydn on 20/01/2019.
//

#ifndef EXMACHINA_CONSTANTS_H
#define EXMACHINA_CONSTANTS_H

#endif //EXMACHINA_CONSTANTS_H
// game state enum
enum{SPLASH_SCREEN, MAIN_MENU, IN_GAME, TEXT_DISPLAY, PAUSE, INVENTORY, GAME_OVER};
// main menu options
enum{NEW_GAME, LOAD_GAME, EXIT_GAME};
// pause menu options
enum{CONTINUE_GAME, SAVE_GAME, QUIT_GAME};
// directions
enum{NORTH, EAST, SOUTH, WEST};

const int NUM_FLOOR_SPRITES = 1;
const int NUM_WALL_SPRITES = 8;
const int NUM_FOREGROUND_SPRITES = 5;
const int NUM_ITEM_SPRITES = 1;
const int NUM_CLUE_SPRITES = 1;
const int NUM_SWITCH_SPRITES = 1;
const int NUM_EXIT_SPRITES = 4;
const int NUM_MOVABLE_SPRITES = 1;
const int NUM_PLAYER_SPRITES = 16;

const int NUM_ROOMS = 2;

const float GAME_HEIGHT = 768.0f;
const float GAME_WIDTH = 1366.0f;
const float GRID_SIZE = 75.0f;
