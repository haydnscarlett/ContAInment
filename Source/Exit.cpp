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
