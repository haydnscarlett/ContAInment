//
// Created by haydn on 20/01/2019.
//

#include "GameObject.h"
#include "Switch.h"
#ifndef EXMACHINA_PUZZLE_H
#define EXMACHINA_PUZZLE_H

class Puzzle
{
 public:
  GameObject* getMyGameobjects() ;
  void setMyGameobjects(GameObject* new_gameobjects);
  int getPuzzleID() ;
  void setPuzzleID(int new_id);
  int* getLinkedExits() ;
  void setLinkedExits(int* new_exits);
  GameObject* getMyMovables() ;
  void setMyMovables(GameObject* new_movables);
  Switch* getMySwitches() ;
  void setMySwitches(Switch* new_switches);
 private:
  GameObject * my_gameobjects;
  int puzzle_id;
  int* linked_exits;
  GameObject* my_movables;
  Switch* my_switches;

};

#endif //EXMACHINA_PUZZLE_H
