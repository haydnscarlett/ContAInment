//
// Created by h2-scarlett on 18/01/2019.
//

#include "GameObject.h"
#include "Constants.h"

/**
*   @brief   Get My Location
*   @details This function returns the Sprite's Location
*   @return  int
*/
Point2D GameObject::getMyLocation()
{
  return location;
}

/**
*   @brief   Set My Location
*   @details This function sets sprite's Location
*   @param   new_location The new loaction
*   @return  void
*/
void GameObject::setMyLocation(Point2D new_location)
{
  location = new_location;
}

/**
*   @brief   Does a another rectangle reside within this rectangle?
*   @details Will check to see if the two rectangles overlap.
*   @return  True if they do.
*/
bool GameObject::isInside(float other_x, float other_y) const
{

  bool xOverlap = isBetween(location.x, other_x, other_x + GRID_SIZE) ||
                  isBetween(other_x, location.x, location.x + GRID_SIZE);

  bool yOverlap = isBetween(location.y, other_y, other_y + GRID_SIZE) ||
                  isBetween(other_y, location.y, location.y + GRID_SIZE);

  return xOverlap && yOverlap;
}

/**
*   @brief   Checks to see if a value falls within a range.
*   @details Takes a value and uses a min and max to generate a
             check to see if the value falls inside it's range.
*   @return  True if they do.
*/
bool GameObject::isBetween(float value, float min, float max) const
{
  return (value >= min) && (value <= max);
}

/**
*   @brief   Collision Check
*   @details Checks to see if this gameobject is colliding with the player
*           gameobject
*   @param   player_location The players location
*   @param   player_direction The player direction
*   @param   double_distance The bool to indicate whether to check double the
*            normal distance used when moving movable objects and for
*            dropping items
*   @return  True if will collide on next move cycle
*/
bool GameObject::collisionCheck(Point2D player_location, int player_direction,
                                bool double_distance)
{
  float distance = 0.0f;
  bool colliding = false;
  if(double_distance)
  {
    distance += GRID_SIZE;
  }
  switch(player_direction)
  {
    case NORTH :

      if (isInside(player_location.x + (GRID_SIZE * DISTANCE_CHECK) ,
                   player_location.y  - distance - (GRID_SIZE * DISTANCE_CHECK))
          && isInside(player_location.x - (GRID_SIZE * DISTANCE_CHECK) ,
                      player_location.y - distance - (GRID_SIZE * DISTANCE_CHECK)))
      {
        colliding = true;
      }
      break;
    case EAST :

      if (isInside(player_location.x + distance + (GRID_SIZE * DISTANCE_CHECK),
                   player_location.y + (GRID_SIZE * DISTANCE_CHECK))
          && isInside(player_location.x + distance + (GRID_SIZE * DISTANCE_CHECK),
                      player_location.y  - (GRID_SIZE * 0.005f)))
      {
        colliding = true;
      }
      break;

    case SOUTH :

      if (isInside(player_location.x + (GRID_SIZE * DISTANCE_CHECK) ,
                   player_location.y + distance +(GRID_SIZE * DISTANCE_CHECK))
          && isInside(player_location.x - (GRID_SIZE * DISTANCE_CHECK) ,
                      player_location.y + distance + (GRID_SIZE *DISTANCE_CHECK)))
      {
        colliding = true;
      }
      break;
    case WEST :

      if (isInside(player_location.x - distance - (GRID_SIZE * DISTANCE_CHECK) ,
                   player_location.y+(GRID_SIZE * DISTANCE_CHECK))
          && isInside(player_location.x - distance - (GRID_SIZE * DISTANCE_CHECK) ,
                      player_location.y - (GRID_SIZE * DISTANCE_CHECK)))
      {
        colliding = true;
      }
      break;
    default :
      break;
  }


  return colliding;
}

/**
*   @brief   Get My Sprite ID
*   @details This function returns the Sprite's ID
*   @return  int
*/
int GameObject::getMySpriteId() const
{
  return my_sprite_id;
}

/**
*   @brief   Set My Sprite Id
*   @details This function sets sprite ID
*   @param   new_my_sprite_id The new sprite ID
*   @return  void
*/
void GameObject::setMySpriteId(int new_my_sprite_id)
{
  my_sprite_id = new_my_sprite_id;
}

/**
*   @brief   Constructor Overload
*   @details This function creates a Exit class with the specified data
*   @param   new_my_sprite_id The Sprite id
*   @param   new_location The location of the sprite
*   @return  GameObject
*/
GameObject::GameObject(int new_my_sprite_id, Point2D new_location)
{
  my_sprite_id = new_my_sprite_id;
  location = new_location;
}

/**
*   @brief   Constructor
*   @details This function creates a default GameObject class
*   @return  GameObject
*/
GameObject::GameObject()
{

  my_sprite_id = -1;
  location.x = 0.0f;
  location.y = 0.0f;
}
