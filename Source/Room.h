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
  GameObject* getMyBackground() ;
  void setMyBackground(GameObject* new_background);
  GameObject* getMyForeground() ;
  void setMyForeground(GameObject* new_foreground);
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
  void reomveItem(int item_ID);
  void addItem(int item_ID);

 private:
  GameObject* my_background;
  GameObject* my_foreground;
  Clue* my_clues;
  Item* my_items;
  Puzzle my_puzzle;
  int room_id;
  Exit* my_exits;
};

#endif //EXMACHINA_ROOM_H
