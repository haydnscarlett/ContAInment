//
// Created by haydn on 20/01/2019.
//

#include "Switch.h"

GameObject Switch::getMyOnGameobject()
{
  return my_on_gameobject;
}

void Switch::setMyOnGameobject(GameObject new_on_gameobject)
{
  my_on_gameobject = new_on_gameobject;
}

GameObject Switch::getMyOffGameobject()
{
  return my_off_gameobject;
}

void Switch::setMyOffGameobject(GameObject new_off_gameobject)
{
  my_off_gameobject = new_off_gameobject;
}

bool Switch::isOn()
{
  return on;
}

void Switch::setOn(bool new_on)
{
  on = new_on;
}



Switch::Switch(GameObject new_on_gameobject, GameObject new_off_gameobject,
               bool new_on)
{
  my_on_gameobject = new_on_gameobject;
  my_off_gameobject = new_off_gameobject;
  on = new_on;
}


Switch::Switch()
{
  Point2D new_location;
  GameObject new_gameobject(-1, new_location);
  my_on_gameobject = new_gameobject;
  my_off_gameobject = new_gameobject;
  on = false;
}