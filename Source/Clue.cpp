//
// Created by h2-scarlett on 18/01/2019.
//

#include "Clue.h"
#include "Constants.h"
/**
 *   @brief   Get My Gameobject
 *   @details This function returns the clue's gameobject
 *   @return  GameObject
 */
GameObject Clue::getMyGameObject()
{
  return my_gameobject;
}

/**
 *   @brief   Set My Gameobject
 *   @details This function sets the clue's gameobject
 *   @param   new_gameobject The Clue Gameobject
 *   @return  void
 */
void Clue::setMyGameObject(GameObject new_gameobject)
{
  my_gameobject = new_gameobject;
}

/**
 *   @brief   Get Clue ID
 *   @details This function returns the clue's ID
 *   @return  int
 */
int Clue::getClueID()
{
  return clue_id;
}

/**
 *   @brief   Add Clue to Player
 *   @details This function adds the clue to the player clues found array
 *   @param   clues_found The Clues found array
 *   @param   index The index in the Clues found array to add the clue to
 *   @return  void
 */
bool Clue::addClueToPlayer(int* clues_found, int index)
{
  for (int i = 0; i < index; i++)
  {
    if (clue_id == clues_found[i])
    {
      return false;
    }
  }
  return true;
}

/**
 *   @brief   Constructor Overload
 *   @details This function creates a Clue class with the specified data
 *   @param   new_gameobject The Clue Gameobject
 *   @param   new_clue_id The clue id
 *   @param   new_item_description The clues text
 *   @return  Clue
 */
Clue::Clue(GameObject new_gameobject, int new_clue_id)
{
  my_gameobject = new_gameobject;
  clue_id = new_clue_id;
}

/**
 *   @brief   Constructor
 *   @details This function creates a default Clue class
 *   @return  Clue
 */
Clue::Clue()
{
  Point2D new_location;
  GameObject new_gameobject(-1, new_location);
  my_gameobject = new_gameobject;
  clue_id = -1;
}