//
// Created by haydn on 20/01/2019.
//
#include "GameObject.h"

#ifndef EXMACHINA_SWITCH_H
#define EXMACHINA_SWITCH_H

class Switch
{
 public:
  GameObject getMyOnGameobject();
  void setMyOnGameobject(GameObject my_on_gameobject);
  GameObject getMyOffGameobject();
  void setMyOffGameobject(GameObject my_off_gameobject);
  bool isOn();
  void setOn(bool on);
 private:
  GameObject my_on_gameobject;
  GameObject my_off_gameobject;
  bool on;

};

#endif //EXMACHINA_SWITCH_H
