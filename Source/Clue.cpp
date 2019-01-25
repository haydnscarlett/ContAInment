//
// Created by h2-scarlett on 18/01/2019.
//

#include "Clue.h"
#include "Constants.h"
GameObject Clue::getMyGameObject()
{
  return my_gameobject;
}
void Clue::setMyGameObject(GameObject new_gameobject)
{
  my_gameobject = new_gameobject;
}
std::string Clue::getItemDescription()
{
  return item_description;
}
void Clue::setItemDescription(std::string new_item_description)
{
  item_description = new_item_description;
}
int Clue::getClueID()
{
  return clue_id;
}
void Clue::setClueID(int new_clue_id)
{
  clue_id = new_clue_id;
}

bool Clue::addClueToPlayer(int* clues_found, int index)
{
  bool already_found = false;
  for (int i = 0; i < index; i ++)
  {
    if (clue_id == clues_found[i])
    {
      already_found = true;
    }
  }
  if (!already_found)
  {
    clues_found = new int[index];
    clues_found[index - 1] = clue_id;
  }
  return already_found;
}

Clue::~Clue()
{

}

