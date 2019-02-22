//
// Created by h2-scarlett on 18/01/2019.
//
#include "GameObject.h"

#ifndef EXMACHINA_CLUE_H
#  define EXMACHINA_CLUE_H

class Clue
{
 public:
  Clue();
  Clue(GameObject new_gameobject, int new_clue_id);
  GameObject getMyGameObject();
  void setMyGameObject(GameObject new_gameobject);
  int getClueID();
  bool addClueToPlayer(int* clues_found, int index);

 private:
  GameObject my_gameobject;
  int clue_id;
};

#endif // EXMACHINA_CLUE_H
