//
// Created by haydn on 20/01/2019.
//

#include "Puzzle.h"
#include "Constants.h"

/**
*   @brief   Set Puzzle ID
*   @details This function sets the puzzle's ID
*   @param   new_id The Puzzle id
*   @return  void
*/
void Puzzle::setPuzzleID(int new_id)
{
  puzzle_id = new_id;
}

/**
*   @brief   Get Linked Exits
*   @details This function returns the Linked Exits array
*   @return  int*
*/
int* Puzzle::getLinkedExits()
{
  return linked_exits;
}

/**
*   @brief   Set Linked Exits
*   @details This function sets the puzzle's Linked Exits arrray
*   @param   new_exits The array of linked exit ID's
*   @return  void
*/
void Puzzle::setLinkedExits(int* new_exits)
{
  linked_exits = new_exits;
}

/**
*   @brief   Get My Movables
*   @details This function returns the Movable Objects array
*   @return  GameObject*
*/
GameObject* Puzzle::getMyMovables()
{
  return my_movables;
}

/**
*   @brief   Set My Movables
*   @details This function sets the puzzle's movable gameobjects array
*   @param   new_movables The array of movable gameobjects
*   @return  void
*/
void Puzzle::setMyMovables(GameObject* new_movables)
{
  my_movables = new_movables;
}

/**
*   @brief   Get My Switches
*   @details This function returns the Switch Objects array
*   @return  GameObject*
*/
Switch* Puzzle::getMySwitches()
{
  return my_switches;
}

/**
*   @brief   Set My Switches
*   @details This function sets the puzzle's Switches array
*   @param   new_switches The array of Switches
*   @return  void
*/
void Puzzle::setMySwitches(Switch* new_switches)
{
  my_switches = new_switches;
}

/**
*   @brief   Get Number Linked Exits
*   @details This function returns the Number of Linked Exits
*   @return  int
*/
int Puzzle::getNumberLinkedExits() const
{
  return number_linked_exits;
}

/**
*   @brief   Set Number Linked Exits
*   @details This function sets the puzzle's Number of Linked Exits
*   @param   new_number_linked_exits The number of linked exits
*   @return  void
*/
void Puzzle::setNumberLinkedExits(int new_number_linked_exits)
{
  number_linked_exits = new_number_linked_exits;
}

/**
*   @brief   Get Number Movables
*   @details This function returns the Number of Movables
*   @return  int
*/
int Puzzle::getNumberMovables() const
{
  return number_movables;
}

/**
*   @brief   Set Number Movables
*   @details This function sets the puzzle's Number of Movables objects
*   @param   new_number_movables The number of Movables objects
*   @return  void
*/
void Puzzle::setNumberMovables(int new_number_movables)
{
  number_movables = new_number_movables;
}

/**
*   @brief   Get Number Switches
*   @details This function returns the Number of Switches
*   @return  int
*/
int Puzzle::getNumberSwitches() const
{
  return number_switches;
}

/**
*   @brief   Set Number Switches
*   @details This function sets the puzzle's Number of Switch objects
*   @param   new_number_switches The number of Switch objects
*   @return  void
*/
void Puzzle::setNumberSwitches(int new_number_switches)
{
  number_switches = new_number_switches;
}

/**
*   @brief   Set Required Item ID
*   @details This function sets the puzzle's Required Item ID
*   @param   new_required_item_id The Item id
*   @return  void
*/
void Puzzle::setRequiredItemID(int new_required_item_id)
{
  required_item_id = new_required_item_id;
}

/**
*   @brief   Set Required Clue ID
*   @details This function sets the puzzle's Required Clue ID
*   @param   new_required_clue_id The Clue id
*   @return  void
*/
void Puzzle::setRequiredClueID(int new_required_clue_id)
{
  required_clue_id = new_required_clue_id;
}

/**
*   @brief   Check Puzzle Completed
*   @details This function returns checks if the puzzle is complete and
*           updates the player and facility power bool accordingly
*   @return  bool
*/
bool Puzzle::checkPuzzleCompleted(Player* player, bool* power_on)
{
  bool puzzle_completed = false;
  bool switches_completed = false;
  bool movables_completed = false;
  bool required_item_completed = false;
  bool required_clue_completed = false;

  if (number_switches == 0)
  {
    switches_completed = true;
  }
  else if (number_switches > 0)
  {
    switches_completed = true;
    for (int i = 0; i < number_switches; i++)
    {
      if(target_switch_states[i] != my_switches[i].isOn())
      {
        switches_completed = false;
      }
    }
  }
  if (number_movables == 0 || puzzle_id == 7)
  {
    movables_completed = true;
  }
  else if (number_movables > 0)
  {
    movables_completed = true;
    for (int i = 0; i < number_movables; i++)
    {
      if(!(my_movables[i].getMyLocation().x > (target_movable_locations[i].x - MOVABLE_DISTANCE_CHECK)
          && my_movables[i].getMyLocation().x < (target_movable_locations[i].x + MOVABLE_DISTANCE_CHECK)
          && (my_movables[i].getMyLocation().y > (target_movable_locations[i].y - MOVABLE_DISTANCE_CHECK)
          && my_movables[i].getMyLocation().y < (target_movable_locations[i].y + MOVABLE_DISTANCE_CHECK))))
      {
        movables_completed = false;
      }
    }
  }


  if (required_item_id == -1)
  {
    required_item_completed = true;
  }
  else if (required_item_id > -1)
  {
    for (int i = 0; i < 15; i++)
    {
      if(player->getInventory(i).getItemID() == required_item_id)
      {
        required_item_completed = true;
      }
    }
  }
  if (required_clue_id == -1)
  {
    required_clue_completed = true;
  }
  else if (required_clue_id > -1)
  {
    for (int i = 0; i < player->getNumberCluesFound(); i++)
    {
      if(player->getCluesFound()[i] == required_clue_id)
      {
        required_clue_completed = true;
      }
    }
  }


  if(switches_completed && movables_completed && required_item_completed &&
      required_clue_completed)
  {
    if((power_required && *power_on) || !power_required)
    {
      puzzle_completed = true;
    }
  }
  return puzzle_completed;
}

/**
*   @brief   Get Target Movable Locations
*   @details This function returns the Target Movable Locations array
*   @return  Point2D*
*/
Point2D* Puzzle::getTargetMovableLocations() const
{
  return target_movable_locations;
}

/**
*   @brief   Set Target Movable Locations
*   @details This function sets the puzzle's Target Movable Locations array
*   @param   new_target_movable_locations The Target Movable Locations array
*   @return  void
*/
void Puzzle::setTargetMovableLocations(Point2D* new_target_movable_locations)
{
  target_movable_locations = new_target_movable_locations;
}

/**
*   @brief   Set Target Switch States
*   @details This function sets the puzzle's Target Switch States array
*   @param   new_target_switch_states The Target Switch States array
*   @return  void
*/
void Puzzle::setTargetSwitchStates(bool* new_target_switch_states)
{
  target_switch_states = new_target_switch_states;
}

/**
*   @brief   Get Puzzle Solved Message
*   @details This function returns the Puzzle Solved Message text
*   @return  std::string
*/
std::string Puzzle::getPuzzleSolvedMessage()
{
  return puzzle_solved_message;
}

/**
*   @brief   Set Target Switch States
*   @details This function sets the puzzle's Target Switch States array
*   @param   new_target_switch_states The Target Switch States array
*   @return  void
*/
void Puzzle::setPuzzleSolvedMessage(std::string new_puzzle_solved_message)
{
  puzzle_solved_message.operator=(new_puzzle_solved_message) ;
}

/**
*   @brief   Set Target Switch States
*   @details This function sets the puzzle's Target Switch States array
*   @param   new_target_switch_states The Target Switch States array
*   @return  void
*/
void Puzzle::setPowerRequired(bool new_power_required)
{
  power_required = new_power_required;
}

Puzzle::Puzzle()
{
  puzzle_id = -1;
  number_linked_exits = 0;
  linked_exits = nullptr;
  number_movables = 0;
  target_movable_locations = nullptr;
  my_movables = nullptr;
  number_switches = 0;
  target_switch_states = nullptr;
  my_switches = nullptr;
  required_item_id = -1;
  required_clue_id = -1;
  puzzle_solved_message = "";
  power_required = false;
}
