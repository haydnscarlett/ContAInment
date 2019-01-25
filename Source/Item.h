//
// Created by h2-scarlett on 18/01/2019.
//
#include "GameObject.h"

#ifndef EXMACHINA_ITEM_H
#  define EXMACHINA_ITEM_H

class Item
{
  public:
  virtual ~Item();
  GameObject getMyGameObject();
  void setMyGameObject(GameObject new_gameobject);
  std::string getItemDescription();
  void setItemDescription(std::string new_item_description);
  std::string getItemName();
  void setItemName(std::string new_item_name);
  int getItemID();
  void setItemID(int new_item_id);
  Item addItemToInventory();

  private:
  GameObject my_gameobject;
  int item_id;
  std::string item_description;
  std::string item_name;
};

#endif // EXMACHINA_ITEM_H
