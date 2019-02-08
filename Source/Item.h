//
// Created by h2-scarlett on 18/01/2019.
//
#include "GameObject.h"

#ifndef EXMACHINA_ITEM_H
#  define EXMACHINA_ITEM_H

class Item
{
  public:
  Item();
  Item(GameObject new_gameobject, int new_item_id);
  GameObject getMyGameObject();
  void setMyGameObject(GameObject new_gameobject);
  int getItemID();
  void setItemID(int new_item_id);
  Item addItemToInventory();

  private:
  GameObject my_gameobject;
  int item_id;
};

#endif // EXMACHINA_ITEM_H
