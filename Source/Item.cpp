//
// Created by h2-scarlett on 18/01/2019.
//

#include "Item.h"
/**
 *   @brief   Get My Gameobject
 *   @details This function returns the Item's gameobject
 *   @return  GameObject
 */
GameObject Item::getMyGameObject()
{
  return my_gameobject;
}

/**
 *   @brief   Set My Gameobject
 *   @details This function sets the Item's gameobject
 *   @param   new_gameobject The Item Gameobject
 *   @return  void
 */
void Item::setMyGameObject(GameObject new_gameobject)
{
  my_gameobject = new_gameobject;
}

/**
 *   @brief   Get Item ID
 *   @details This function returns the Item's ID
 *   @return  int
 */
int Item::getItemID()
{
  return item_id;
}

/**
 *   @brief   Set Item ID
 *   @details This function sets the Item's ID
 *   @param   new_item_id The Item ID
 *   @return  void
 */
void Item::setItemID(int new_item_id)
{
  item_id = new_item_id;
}

Item Item::addItemToInventory()
{
  return *this;
}

/**
 *   @brief   Constructor Overload
 *   @details This function creates a Item class with the specified data
 *   @param   new_gameobject The Item Gameobject
 *   @param   new_item_id The Item id
 *   @return  Item
 */
Item::Item(GameObject new_gameobject, int new_item_id)
{
  my_gameobject = new_gameobject;
  item_id = new_item_id;
}

/**
 *   @brief   Constructor
 *   @details This function creates a default Item class
 *   @return  Item
 */
Item::Item()
{
  Point2D new_location;
  GameObject new_gameobject(-1, new_location);
  my_gameobject = new_gameobject;
  item_id = -1;
}