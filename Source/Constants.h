//
// Created by haydn on 20/01/2019.
//
#include <string>

#ifndef EXMACHINA_CONSTANTS_H
#  define EXMACHINA_CONSTANTS_H

#endif // EXMACHINA_CONSTANTS_H
// game state enum
enum
{
  SPLASH_SCREEN,
  MAIN_MENU,
  IN_GAME,
  TEXT_DISPLAY,
  PAUSE,
  INVENTORY,
  GAME_OVER,
  JOURNAL,
  MAP
};
// main menu options
enum
{
  NEW_GAME,
  LOAD_GAME,
  EXIT_GAME
};
// pause menu options
enum
{
  CONTINUE_GAME,
  SAVE_GAME,
  QUIT_GAME
};
// directions
enum
{
  NORTH,
  EAST,
  SOUTH,
  WEST
};
// foreground sprites
enum
{
  COUNTER_LEFT,
  COUNTER_RIGHT,
  TABLE_TOP,
  TABLE_MIDDLE,
  TABLE_BOTTOM,
  FRIDGE_TOP,
  SINK_TOP,
  TABLE_LEFT,
  TABLE_CENTRE,
  TABLE_RIGHT,
  CHAIR_TOP,
  CHAIR_BOTTOM,
  COOKER_TOP,
  CAFE_TABLE_LEFT,
  CAFE_TABLE_RIGHT,
  SOFA_TOP_LEFT,
  SOFA_TOP_RIGHT,
  SOFA_LEFT_TOP,
  SOFA_LEFT_BOTTOM,
  SOFA_RIGHT_TOP,
  SOFA_RIGHT_BOTTOM,
  SOFA_BOTTOM_LEFT,
  SOFA_BOTTOM_RIGHT,
  BED_LEFT,
  BED_RIGHT,
  BED_TOP,
  BED_BOTTOM,
  FLOWER_TOP,
  FLOWER_MID_ONE,
  FLOWER_MID_TWO,
  FLOWER_BOTTOM,
  LAB_COAT,
  VENDING_MACHINE,
  WEIGHTBENCH_TOP,
  WEIGHTBENCH_BOTTOM,
  TREADMILL_TOP,
  TREADMILL_BOTTOM,
  LOCKER_TOP,
  LOCKER_BOTTOM,
  SHOWER,
  TOILET_LEFT,
  BATHROOM_SINK_RIGHT,
  WASTE_BARREL,
  WASTE_BARREL_TWO,
  BOOKSHELF_LEFT,
  BOOKSHELF_RIGHT,
  STORAGE_CRATE,
  SYNTH_TOP_LEFT,
  SYNTH_TOP_RIGHT,
  SYNTH_BOTTOM_LEFT,
  SYNTH_BOTTOM_RIGHT,
  SYNTH_TERMINAL,
  SURGEONS_TOOLS,
  POOL_TOP_LEFT,
  POOL_TOP_RIGHT,
  POOL_BOTTOM_LEFT,
  POOL_BOTTOM_RIGHT,
  COMPUTERS_TOP_LEFT,
  COMPUTERS_TOP_CENTRE,
  COMPUTERS_TOP_RIGHT,
  COMPUTERS_LEFT_MIDDLE,
  COMPUTERS_LEFT_BOTTOM,
  COMPUTERS_RIGHT_MIDDLE,
  COMPUTERS_RIGHT_BOTTOM,
  SYNTH_BRAIN,
  REACTOR_TOP_LEFT,
  REACTOR_TOP_RIGHT,
  REACTOR_MIDDLE_LEFT,
  REACTOR_MIDDLE_RIGHT,
  REACTOR_BOTTOM_LEFT,
  REACTOR_BOTTOM_RIGHT,
  DESK_RIGHT,
  DESK_LEFT,
  DESK_CHAIR_BOTTOM,
  SAFE,
  SERVER_LEFT,
  SERVER_RIGHT
};
// Wall sprites
enum
{
  TOP_LEFT,
  TOP,
  TOP_RIGHT,
  LEFT,
  RIGHT,
  BOTTOM_LEFT,
  BOTTOM,
  BOTTOM_RIGHT
};
// rooms
enum
{
  OFFICE_ONE,
  ATRIUM,
  CAFETERIA,
  LOUNGE,
  DORMS,
  GARDEN,
  GYM,
  LOCKERS,
  TOILETS_M,
  TOILETS_F,
  WASTE_DISPOSAL,
  LIBRARY,
  SUPPLY_ROOM,
  CORRIDOR,
  LAB_ONE,
  LAB_TWO,
  OBSERVATION,
  TESTING,
  SERVERS,
  REACTOR,
  WORKSHOP,
  INFIRMARY,
  LEAD_TECH_OFFICE,
  SECURITY,
  RECEPTION,
  EXIT
};
// items
enum
{
  SCREWDRIVER,
  FUSE,
  KEYCARD_BLUE,
  CAN,
  LUNCHBOX,
  KEY,
  KEYCARD_RED,
  KEYCARD_GREEN,
  KEYCARD_YELLOW,
  HAMMER,
  PLIERS,
  MAGNIFIER
};

// number of sprites for sprite arrays
const int NUM_FLOOR_SPRITES = 3;
const int NUM_WALL_SPRITES = 8;
const int NUM_FOREGROUND_SPRITES = 77;
const int NUM_ITEM_SPRITES = 12;
const int NUM_CLUE_SPRITES = 2;
const int NUM_SWITCH_SPRITES = 1;
const int NUM_EXIT_SPRITES = 4;
const int NUM_MOVABLE_SPRITES = 1;
const int NUM_PLAYER_SPRITES = 16;
const int NUM_CLUES = 11;
// number of rooms in the game
const int NUM_ROOMS = 25;

// the game windows height and width
const float GAME_HEIGHT = 768.0f;
const float GAME_WIDTH = 1366.0f;

// the size of a game sprite
const float GRID_SIZE = 75.0f;

// the distance tolerance check used for collision
const float DISTANCE_CHECK = 0.005f;

// the distance tolerance check used for checking if a puzzle is completed
const float MOVABLE_DISTANCE_CHECK = 0.025f;

// the distance to move the room in the update function whilst the player is
// moving
const float MOVEMENT_DISTANCE = 0.25f;

const std::string ITEM_NAMES[13] = { "Screwdriver",
                                     "Fuse",
                                     "Yellow Keycard",
                                     "Blue Keycard",
                                     "Can",
                                     "Lunch box",
                                     "Can",
                                     "Key",
                                     "Hammer",
                                     "Pliers",
                                     "Red Keycard",
                                     "Green Keycard",
                                     "Magnifying glass." };
const std::string ITEM_DESCRIPTIONS[13] = { "You found a screwdriver.",
                                            "You found a fuse.",
                                            "You found a yellow keycard.",
                                            "You found a blue keycard.",
                                            "You found a can.",
                                            "You found a lunch box.",
                                            "You found a can.",
                                            "You found the key to the reactor room.",
                                            "You found a hammer",
                                            "You found a pair of pliers.",
                                            "You found a red keycard.",
                                            "You found a green keycard.",
                                            "You found a Magnifying glass." };
const std::string CLUES[NUM_CLUES] = { "There is no power.",
                                       "There is a spare reactor fuse in the lab "
                                       "coat in the garden, did you leave "
                                       "it there \n"
                                       "on purpose?",
                                       "8197",
                                       "IMPORTANT: In case of an "
                                       "Emergency password is 'SANE'",
                                       "Hey hun, waiting at the reception ;)",
                                       "Reading list: Reprogrammimng the brain, "
                                       "Modern Neuroscience  \n"
                                       "Advanced AI, AI Pattern Recogniton, Printing"
                                       " Synthetic organs, The synthetic Human.",
                                       "This has been used recently, "
                                       "could it be? FIBI?",
                                       "What is this? We were using human "
                                       "brains, \nno no no, this can’t "
                                       "be happening!",
                                       "Power continues to cut out, i'm "
                                       "starting to think it's not a "
                                       "coincidence, \n"
                                       "i'll keep the key to the reactor "
                                       "in my safe until the issue "
                                       "is resolved.",
                                       "Keycards: Red = Emergency exit from Atrium,"
                                       " Green = Waste Disposal, \nYellow = Labs,"
                                       " Blue = Reception Exit",
                                       "10101 for power" };