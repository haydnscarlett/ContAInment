//
// Created by haydn on 20/01/2019.
//

#include "Switch.h"
/**
*   @brief   Get Switch On Gameobject
*   @details This function returns the Switch on gameobject
*   @return  GameObject
*/
GameObject Switch::getMyOnGameobject()
{
  return my_on_gameobject;
}

/**
*   @brief   Set Switch on Gameobject
*   @details This function sets the Switch on gameobject
*   @param   new_on_gameobject The new Switch on Gameobject
*   @return  void
*/
void Switch::setMyOnGameobject(GameObject new_on_gameobject)
{
  my_on_gameobject = new_on_gameobject;
}

/**
*   @brief   Get Switch off Gameobject
*   @details This function returns the Switch off gameobject
*   @return  GameObject
*/
GameObject Switch::getMyOffGameobject()
{
  return my_off_gameobject;
}

/**
*   @brief   Set Switch off Gameobject
*   @details This function sets the Switch off gameobject
*   @param   new_off_gameobject The new Switch off Gameobject
*   @return  void
*/
void Switch::setMyOffGameobject(GameObject new_off_gameobject)
{
  my_off_gameobject = new_off_gameobject;
}

/**
*   @brief   Is On
*   @details This function returns the state of the switch object
*   @return  bool
*/
bool Switch::isOn()
{
  return on;
}

/**
*   @brief   Set On
*   @details This function sets the Switch on or off state
*   @param   new_on The state of the switch true for on false for off
*   @return  void
*/
void Switch::setOn(bool new_on)
{
  on = new_on;
}

/**
*   @brief   Constructor Overload
*   @details This function creates a Switch class with the specified data
*   @param   new_on_gameobject The Switch on Gameobject
*   @param   new_off_gameobject The Switch off Gameobject
*   @param   new_on The bool for whether the switch is on or off
*   @return  Switch
*/
Switch::Switch(GameObject new_on_gameobject, GameObject new_off_gameobject,
               bool new_on)
{
  my_on_gameobject = new_on_gameobject;
  my_off_gameobject = new_off_gameobject;
  on = new_on;
}

/**
*   @brief   Constructor
*   @details This function creates a default Switch class
*   @return  Switch
*/
Switch::Switch()
{
  Point2D new_location;
  GameObject new_gameobject(-1, new_location);
  my_on_gameobject = new_gameobject;
  my_off_gameobject = new_gameobject;
  on = false;
}