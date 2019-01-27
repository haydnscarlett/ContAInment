//
// Created by haydn on 20/01/2019.
//

#include "Exit.h"

GameObject Exit::getMyExitGameobject()
{
  return my_exit_gameobject;
}

void Exit::setMyExitGameobject( GameObject new_exit_gameobject)
{
  my_exit_gameobject = new_exit_gameobject;
}

int Exit::getExitID()
{
  return exit_id;
}

void Exit::setExitID(int new_exit_ID)
{
  exit_id = new_exit_ID;
}

int Exit::getConnectedRoomID()
{
  return connected_room_id;
}

void Exit::setConnectedRoomID(int new_connected_room_id)
{
  connected_room_id = new_connected_room_id;
}

int Exit::getConnectedExitID()
{
  return connected_exit_id;
}

void Exit::setConnectedExitID(int new_connected_exit_id)
{
  connected_exit_id = new_connected_exit_id;
}

bool Exit::isLocked()
{
  return locked;
}

void Exit::setLocked(bool new_locked)
{
  locked = new_locked;
}

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
Exit::Exit(GameObject new_gameobject, int new_exit_id, int new_connected_room_id,
int new_connected_exit_id, bool new_locked)
{

  my_exit_gameobject = new_gameobject;
  exit_id = new_exit_id;
  connected_room_id = new_connected_room_id;
  connected_exit_id = new_connected_exit_id;
  locked = new_locked;
}