//
// Created by haydn on 20/01/2019.
//

#include "Puzzle.h"

GameObject* Puzzle::getMyGameobjects()
{
  return my_gameobjects;
}

void Puzzle::setMyGameobjects(GameObject* new_gameobjects)
{
  my_gameobjects = new_gameobjects;
}

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
