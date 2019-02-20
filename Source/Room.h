//
// Created by haydn on 20/01/2019.
//

#include "Clue.h"
#include "Exit.h"
#include "GameObject.h"
#include "Item.h"
#include "Puzzle.h"
#include "soloud.h"
#include "soloud_wav.h"

#ifndef EXMACHINA_ROOM_H
#  define EXMACHINA_ROOM_H

class Room
{
 public:
  GameObject* getMyBackground();
  void setMyBackground(GameObject* new_background);
  GameObject* getMyForeground();
  void setMyForeground(GameObject* new_foreground);
  GameObject* getMyWalls();
  Clue* getMyClues();
  void setMyClues(Clue* new_clues);
  Item* getMyItems();
  void setMyItems(Item* new_items);
  Puzzle getMyPuzzle();
  void setMyPuzzle(const Puzzle& new_puzzle);
  int getRoomID();
  void setRoomID(int new_id);
  Exit* getMyExits();
  void setMyExits(Exit* new_exits);
  void removeItem(int item_ID);
  void addItem(Item new_item);
  int getMyGridsizeX();
  void setMyGridsizeX(int new_gridsize_x);
  int getMyGridsizeY();
  void setMyGridsizeY(int new_gridsize_y);
  int getNumberClues() const;
  void setNumberClues(int number_of_clues);
  int getNumberItems() const;
  void setNumberItems(int number_of_items);
  int getNumberExits() const;
  void setNumberExits(int number_of_exits);
  void moveRoom(Player* player);
  bool checkCollisions(Player* player, bool add_item_check);
  bool checkMovableCollisions(Player* player, bool add_item_check);
  void resetRoomPosition(Point2D distance);
  int checkForInteractables(Player* player, std::string* text_to_display, bool* power_on);
  void checkExits(
    Player* player, std::string* text_to_display, int* game_state, bool power_on, int* exit_check);
  void saveRoom();
  void loadRoom();
  void setupFloorStandard();
  void setupWalls();

 private:
  GameObject* my_background = nullptr;
  GameObject* my_foreground= nullptr;
  GameObject* my_walls= nullptr;
  Clue* my_clues= nullptr;
  int number_of_clues= 0;
  Item* my_items= nullptr;
  int number_of_items= 0;
  Puzzle my_puzzle;
  int room_id = 0;
  Exit* my_exits= nullptr;
  int number_of_exits= 0;
  int my_gridsize_x= 0;
  int my_gridsize_y= 0;
};

#endif // EXMACHINA_ROOM_H
