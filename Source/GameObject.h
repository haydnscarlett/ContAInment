//
// Created by h2-scarlett on 18/01/2019.
//

#include <Engine/Point2D.h>
#include <Engine/Sprite.h>

#ifndef EXMACHINA_GAMEOBJECT_H
#  define EXMACHINA_GAMEOBJECT_H

class GameObject
{
  public:
  ASGE::Sprite* getMySprite();

  public:
  void setMySprite(ASGE::Sprite* new_sprite);

  public:
  Point2D getMyLocation();

  public:
  void setMyLocation(Point2D new_location);

  private:
  ASGE::Sprite* my_sprite;

  private:
  Point2D location;
};

#endif // EXMACHINA_GAMEOBJECT_H
