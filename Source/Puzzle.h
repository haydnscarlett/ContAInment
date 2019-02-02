//
// Created by haydn on 20/01/2019.
//

#include "GameObject.h"
#include "Switch.h"
#include "Player.h"
#ifndef EXMACHINA_PUZZLE_H
#define EXMACHINA_PUZZLE_H

class Puzzle
{
 public:
  int getPuzzleID() ;
  void setPuzzleID(int new_id);
  int* getLinkedExits() ;
  void setLinkedExits(int* new_exits);
  GameObject* getMyMovables() ;
  void setMyMovables(GameObject* new_movables);
  Switch* getMySwitches() ;
  void setMySwitches(Switch* new_switches);
  int getNumberLinkedExits() const;
  void setNumberLinkedExits(int new_number_linked_exits);
  int getRequiredItemID() const;
  void setRequiredItemID(int new_required_item_id);
  int getRequiredClueID() const;
  void setRequiredClueID(int new_required_clue_id);
  int getNumberMovables() const;
  void setNumberMovables(int new_number_movables);
  int getNumberSwitches() const;
  void setNumberSwitches(int new_number_switches);
  bool checkPuzzleCompleted(Player* player, bool* power_on);
  Point2D* getTargetMovableLocations() const;
  void setTargetMovableLocations(Point2D* new_target_movable_locations);
  bool* getTargetSwitchStates() const;
  void setTargetSwitchStates(bool* new_target_switch_states);
  std::string getPuzzleSolvedMessage();
  void setPuzzleSolvedMessage(std::string new_puzzle_solved_message);
  bool isPowerRequired();
  void setPowerRequired(bool power_required);

 private:
  int puzzle_id;
  int number_linked_exits;
  int* linked_exits;
  int number_movables;
  Point2D* target_movable_locations;
  GameObject* my_movables;
  int number_switches;
  bool* target_switch_states;
  Switch* my_switches;
  int required_item_id;
  int required_clue_id;
  std::string puzzle_solved_message;
  bool power_required;
};

#endif //EXMACHINA_PUZZLE_H
