//
// Created by haydn on 20/01/2019.
//

#include "GameObject.h"
#ifndef EXMACHINA_EXIT_H
#define EXMACHINA_EXIT_H

class Exit
{
 public:
  GameObject getMyExitGameobject();
  void setMyExitGameobject(GameObject new_exit_gameobject);
  int getExitID() ;
  void setExitID(int new_exit_ID);
  int getConnectedRoomID() ;
  void setConnectedRoomID(int new_connected_room_id);
  int getConnectedExitID() ;
  void setConnectedExitID(int new_connected_exit_id);
  bool isLocked();
  void setLocked(bool new_locked);
 private:
  GameObject my_exit_gameobject;
  int exit_id;
  int connected_room_id;
  int connected_exit_id;
  bool locked;

};

#endif //EXMACHINA_EXIT_H
