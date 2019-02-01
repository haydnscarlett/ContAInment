//
// Created by haydn on 20/01/2019.
//

#include "Puzzle.h"
#include "Constants.h"

int Puzzle::getPuzzleID()
{
  return puzzle_id;
}

void Puzzle::setPuzzleID(int new_id)
{
  puzzle_id = new_id;
}

int* Puzzle::getLinkedExits()
{
  return linked_exits;
}

void Puzzle::setLinkedExits(int* new_exits)
{
  linked_exits = new_exits;
}

GameObject* Puzzle::getMyMovables()
{
  return my_movables;
}

void Puzzle::setMyMovables(GameObject* new_movables)
{
  my_movables = new_movables;
}

Switch* Puzzle::getMySwitches()
{
  return my_switches;
}

void Puzzle::setMySwitches(Switch* new_switches)
{
  my_switches = new_switches;
}

int Puzzle::getNumberLinkedExits() const
{
  return number_linked_exits;
}

void Puzzle::setNumberLinkedExits(int new_number_linked_exits)
{
  number_linked_exits = new_number_linked_exits;
}

int Puzzle::getRequiredItemID() const
{
  return required_item_id;
}

int Puzzle::getRequiredClueID() const
{
  return required_clue_id;
}
int Puzzle::getNumberMovables() const
{
  return number_movables;
}

void Puzzle::setNumberMovables(int new_number_movables)
{
  number_movables = new_number_movables;
}

int Puzzle::getNumberSwitches() const
{
  return number_switches;
}

void Puzzle::setNumberSwitches(int new_number_switches)
{
  number_switches = new_number_switches;
}

void Puzzle::setRequiredItemID(int new_required_item_id)
{
  required_item_id = new_required_item_id;
}
void Puzzle::setRequiredClueID(int new_required_clue_id)
{
  required_clue_id = new_required_clue_id;
}

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
      player->setNumberPuzzlesSolved(player->getNumberPuzzlesSolved() + 1);

      int* tmp = new int[player->getNumberPuzzlesSolved()];
      for(int i = 0; i < player->getNumberPuzzlesSolved() - 1; i++)
      {
        tmp[i] = player->getPuzzlesSolved()[i];
      }
      tmp[player->getNumberPuzzlesSolved() - 1] = puzzle_id;
      puzzle_completed = true;
      player->setCluesFound(tmp);
    }
  }
  return puzzle_completed;
}

Point2D* Puzzle::getTargetMovableLocations() const
{
  return target_movable_locations;
}

void Puzzle::setTargetMovableLocations(Point2D* new_target_movable_locations)
{
  target_movable_locations = new_target_movable_locations;
}

bool* Puzzle::getTargetSwitchStates() const
{
  return target_switch_states;
}

void Puzzle::setTargetSwitchStates(bool* new_target_switch_states)
{
  target_switch_states = new_target_switch_states;
}

std::string Puzzle::getPuzzleSolvedMessage()
{
  return puzzle_solved_message;
}

void Puzzle::setPuzzleSolvedMessage(std::string new_puzzle_solved_message)
{
  puzzle_solved_message = new_puzzle_solved_message;
}

bool Puzzle::isPowerRequired()
{
  return power_required;
}

void Puzzle::setPowerRequired(bool new_power_required)
{
  power_required = new_power_required;
}
