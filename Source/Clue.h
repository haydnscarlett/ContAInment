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
  Clue(GameObject new_gameobject, int new_clue_id,
       std::string new_item_description);
  virtual ~Clue();
  GameObject getMyGameObject();
  void setMyGameObject(GameObject new_gameobject);
  std::string getItemDescription();
  void setItemDescription(std::string new_item_description);
  int getClueID();
  void setClueID(int new_clue_id);
  bool addClueToPlayer(int* clues_found, int index);

  private:
  GameObject my_gameobject;
  int clue_id;
  std::string item_description;
};

#endif // EXMACHINA_CLUE_H
