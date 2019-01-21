//
// Created by haydn on 20/01/2019.
//

#include "Room.h"

GameObject* Room::getMyBackground()
{
  return my_background;
}

void Room::setMyBackground(GameObject* new_background)
{
  my_background = new_background;
}

GameObject* Room::getMyForeground()
{
  return my_foreground;
}

void Room::setMyForeground(GameObject* new_foreground)
{
  my_foreground = new_foreground;
}

Clue* Room::getMyClues()
{
  return my_clues;
}

void Room::setMyClues(Clue* new_clues)
{
  my_clues = new_clues;
}

Item* Room::getMyItems()
{
  return my_items;
}

void Room::setMyItems(Item* new_items)
{
  my_items = new_items;
}

 Puzzle Room::getMyPuzzle()
{
  return my_puzzle;
}

void Room::setMyPuzzle(Puzzle new_puzzle)
{
  my_puzzle = new_puzzle;
}

int Room::getRoomID()
{
  return room_id;
}

void Room::setRoomID(int new_id)
{
  room_id = new_id;
}

Exit* Room::getMyExits()
{
  return my_exits;
}

void Room::setMyExits(Exit* new_exits)
{
  my_exits = new_exits;
}

void reomveItem(int item_ID)
{
  
}
void addItem(int item_ID)
{
  
}