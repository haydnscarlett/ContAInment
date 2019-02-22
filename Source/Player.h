//
// Created by haydn on 20/01/2019.
//
#include "GameObject.h"
#include "Item.h"
#include <Engine/DebugPrinter.h>
#include <Engine/FileIO.h>

#ifndef EXMACHINA_PLAYER_H
#  define EXMACHINA_PLAYER_H

class Player
{
 public:
  Player();
  GameObject getPlayerGameobject();
  void setPlayerGameobject(GameObject player_gameobject);
  Item getInventory(int index);
  void addToInventory(Item new_item, int index);
  void addToClues(int new_clue, int index);
  int* getCluesFound();
  int getDirection();
  void setDirection(int direction);
  bool isMoving();
  void setMoving(bool moving);
  int getSpriteIndex();
  int getNumberCluesFound();
  void savePlayerData();
  void loadPlayerData();
  void movePlayer(double animation_counter);
  void setupPlayer();
  int getClueFound(int index);
  bool hasItem(int item_id);

 private:
  GameObject player_gameobject;
  Item inventory[15];
  int* clues_found;
  int number_clues_found;
  int direction;
  bool moving;
  int sprite_index;
};

#endif // EXMACHINA_PLAYER_H
