//
// Created by haydn on 20/01/2019.
//

#include "Exit.h"

/**
*   @brief   Get My Exit Gameobject
*   @details This function returns the exit's gameobject
*   @return  GameObject
*/
GameObject Exit::getMyExitGameobject()
{
  return my_exit_gameobject;
}

/**
*   @brief   Set My Exit Gameobject
*   @details This function sets the Exit's gameobject
*   @param   new_exit_gameobject The Exit Gameobject
*   @return  void
*/
void Exit::setMyExitGameobject( GameObject new_exit_gameobject)
{
  my_exit_gameobject = new_exit_gameobject;
}

/**
*   @brief   Get My Exit ID
*   @details This function returns the exit's ID
*   @return  int
*/
int Exit::getExitID()
{
  return exit_id;
}

/**
*   @brief   Get My connected room ID
*   @details This function returns the exit's connected room id
*   @return  int
*/
int Exit::getConnectedRoomID()
{
  return connected_room_id;
}

/**
*   @brief   Get My connected exit ID
*   @details This function returns the exit's connected exit id
*   @return  int
*/
int Exit::getConnectedExitID()
{
  return connected_exit_id;
}

/**
*   @brief   Is locked
*   @details This function returns the exit's locked state
*   @return  bool
*/
bool Exit::isLocked()
{
  return locked;
}

/**
*   @brief   Set locked
*   @details This function sets the exit's locked state
*   @param   new_locked The state of the exit true for locked false for unlocked
*   @return  void
*/
void Exit::setLocked(bool new_locked)
{
  locked = new_locked;
}

/**
*   @brief   Constructor
*   @details This function creates a default Exit class
*   @return  Exit
*/
Exit::Exit()
{
  Point2D new_location;
  GameObject new_gameobject(-1, new_location);
  my_exit_gameobject = new_gameobject;
  exit_id = -1;
  connected_room_id = -1;
  connected_exit_id = -1;
  locked = false;
}

/**
*   @brief   Constructor Overload
*   @details This function creates a Exit class with the specified data
*   @param   new_gameobject The Exit Gameobject
*   @param   new_exit_id The Exit id
*   @param   new_connected_room_id The room the door is connected to
*   @param   new_connected_exit_id The exit the door is connected to in the
*            connected room
*   @param   new_locked The state of the exit true for locked false for unlocked
*   @return  Exit
*/
Exit::Exit(GameObject new_gameobject, int new_exit_id, int new_connected_room_id,
int new_connected_exit_id, bool new_locked)
{

  my_exit_gameobject = new_gameobject;
  exit_id = new_exit_id;
  connected_room_id = new_connected_room_id;
  connected_exit_id = new_connected_exit_id;
  locked = new_locked;
}