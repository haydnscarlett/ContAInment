//
// Created by haydn on 20/01/2019.
//
#include <Engine/FileIO.h>
#include <Engine/DebugPrinter.h>
#include "GameObject.h"
#include "Item.h"

#ifndef EXMACHINA_PLAYER_H
#define EXMACHINA_PLAYER_H

class Player
{
 public:
  GameObject getPlayerGameobject() ;
  void setPlayerGameobject( GameObject player_gameobject);
  ASGE::Sprite* getPlayerSprite(int index) ;
  void setPlayerSprites(ASGE::Sprite* player_sprites[]);
  Item getInventory(int index) ;
  void addToInventory(Item new_item, int index) ;
  int* getCluesFound() ;
  void setCluesFound(int* clues_found);
  int* getPuzzlesSolved() ;
  void setPuzzlesSolved(int* puzzles_solved);
  int getDirection() ;
  void setDirection(int direction);
  bool isMoving() ;
  void setMoving(bool moving);
  int getSpriteIndex() ;
  void setSpriteIndex(int new_sprite_index);
  int getNumberCluesFound() ;
  void setNumberCluesFound(int new_number_clues_found);
  int getNumberPuzzlesSolved() ;
  void setNumberPuzzlesSolved(int new_number_puzzles_solved);
  void savePlayerData();
  void loadPlayerData();
  void movePlayer(double animation_counter);
  void setupPlayer(ASGE::Sprite* new_sprites[]);


 private:
  GameObject player_gameobject;
  ASGE::Sprite* player_sprites[16];
  Item inventory[15] ;
  int* clues_found;
  int number_clues_found;
  int* puzzles_solved;
  int number_puzzles_solved;
  int direction;
  bool moving;
  int sprite_index;

};

#endif //EXMACHINA_PLAYER_H
