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
  Player();
  Player(GameObject new_player_gameobject, Item inventory[],
         int* new_clues_found, int new_number_clues_found,
         int* new_puzzles_solved, int new_number_puzzles_solved,
         int new_direction, bool new_moving, int new_sprite_index);
  GameObject getPlayerGameobject() ;
  void setPlayerGameobject( GameObject player_gameobject);
  Item getInventory(int index) ;
  void addToInventory(Item new_item, int index) ;
  void addToClues(int new_clue, int index) ;
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
  void setupPlayer();
  int getClueFound(int index);


 private:
  GameObject player_gameobject;
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
