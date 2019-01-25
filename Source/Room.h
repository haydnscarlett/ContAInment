//
// Created by haydn on 20/01/2019.
//

#include "GameObject.h"
#include "Clue.h"
#include "Item.h"
#include "Puzzle.h"
#include "Exit.h"

#ifndef EXMACHINA_ROOM_H
#define EXMACHINA_ROOM_H

class Room
{
 public:
  virtual ~Room();
  GameObject* getMyBackground() ;
  void setMyBackground(GameObject* new_background);
  GameObject* getMyForeground() ;
  void setMyForeground(GameObject* new_foreground);
  GameObject* getMyWalls() ;
  void setMyWalls(GameObject* new_walls);
  Clue* getMyClues() ;
  void setMyClues(Clue* new_clues);
  Item* getMyItems() ;
  void setMyItems(Item* new_items);
  Puzzle getMyPuzzle() ;
  void setMyPuzzle(Puzzle new_puzzle);
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
  void moveRoom(bool moving, int direction);
  bool checkCollisions(Player* player, std::string* text_to_display,
                       int* game_state);
  bool checkForInteractables(Player* player, std::string* text_to_display);

 private:
  GameObject* my_background;
  GameObject* my_foreground;
  GameObject* my_walls;
  Clue* my_clues;
  int number_of_clues;
  Item* my_items;
  int number_of_items;
  Puzzle my_puzzle;
  int room_id;
  Exit* my_exits;
  int number_of_exits;
  int my_gridsize_x;
  int my_gridsize_y;

};

#endif //EXMACHINA_ROOM_H
