//
// Created by h2-scarlett on 18/01/2019.
//
#include "GameObject.h"

#include "Item.h"
GameObject Item::getMyGameObject()
{
  return my_gameobject;
}
void Item::setMyGameObject(GameObject new_gameobject)
{
  my_gameobject = new_gameobject;
}
std::string Item::getItemDescription()
{
  return item_description;
}
void Item::setItemDescription(std::string new_item_description)
{
  item_description = new_item_description;
}
std::string Item::getItemName()
{
  return item_name;
}
void Item::setItemName(std::string new_item_name)
{
  item_name = new_item_name;
}
int Item::getItemID()
{
  return item_id;
}
void Item::setItemID(int new_item_id)
{
  item_id = new_item_id;
}
int Item::getItemOneRequired()
{
  return item_required_one;
}
void Item::setItemOneRequired(int new_id)
{
  item_required_one = new_id;
}
int Item::getItemTwoRequired()
{
  return item_required_two;
}
void Item::setItemTwoRequired(int new_id)
{
  item_required_two = new_id;
}
void Item::craftItem(int* inventory) {}
void Item::addItemToInventory(int* inventory) {}