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
  GameObject();
  GameObject(int my_sprite_id, Point2D location);
  virtual ~GameObject();
  Point2D getMyLocation();
  void setMyLocation(Point2D new_location);
  bool isBetween(float value, float min, float max) const;
  bool isInside(float other_x, float other_y) const;
  bool collisionCheck(Point2D player_location, int player_direction,
                      bool double_distance);
  int getMySpriteId() const;
  void setMySpriteId(int new_my_sprite_id);

 private:
  int my_sprite_id;
  Point2D location;
};

#endif // EXMACHINA_GAMEOBJECT_H
