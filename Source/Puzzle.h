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
  void setPuzzleID(int new_id);
  int* getLinkedExits() ;
  void setLinkedExits(int* new_exits);
  GameObject* getMyMovables() ;
  void setMyMovables(GameObject* new_movables);
  Switch* getMySwitches() ;
  void setMySwitches(Switch* new_switches);
  int getNumberLinkedExits() const;
  void setNumberLinkedExits(int new_num_lnkd_exts);
  void setRequiredItemID(int new_required_item_id);
  void setRequiredClueID(int new_required_clue_id);
  int getNumberMovables() const;
  void setNumberMovables(int new_number_movables);
  int getNumberSwitches() const;
  void setNumberSwitches(int new_number_switches);
  bool checkPuzzleCompleted(Player* player, bool* power_on);
  Point2D* getTargetMovableLocations() const;
  void setTargetMovableLocations(Point2D* new_tar_mov_locs);
  void setTargetSwitchStates(bool* new_tar_sw_state);
  std::string getPuzzleSolvedMessage();
  void setPuzzleSolvedMessage(std::string new_solved_mssge);
  void setPowerRequired(bool power_required);
  Puzzle();
 private:
  int puzzle_id;
  int number_linked_exits;
  int* linked_exits;
  int number_movables;
  Point2D* targ_movable_locs;
  GameObject* my_movables;
  int number_switches;
  bool* target_switch_states;
  Switch* my_switches;
  int required_item_id;
  int required_clue_id;
  std::string solved_message;
  bool power_required;
};

#endif //EXMACHINA_PUZZLE_H
