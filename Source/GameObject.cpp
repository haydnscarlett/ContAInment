//
// Created by h2-scarlett on 18/01/2019.
//

#include "GameObject.h"

ASGE::Sprite* GameObject::getMySprite()
{
  return my_sprite;
}
void GameObject::setMySprite(ASGE::Sprite* new_sprite)
{
  my_sprite = new_sprite;
}
Point2D GameObject::getMyLocation()
{
  return location;
}
void GameObject::setMyLocation(Point2D new_location)
{
  location = new_location;
}