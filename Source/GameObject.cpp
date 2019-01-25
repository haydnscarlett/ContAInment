//
// Created by h2-scarlett on 18/01/2019.
//

#include "GameObject.h"
#include "Constants.h"

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


ASGE::Sprite* GameObject::getMySprite() const
{
  return my_sprite;
}



/**
*   @brief   Does a another rectangle reside within this rectangle?
*   @details Will check to see if the two rectanges overlap.
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


bool GameObject::collisionCheck(Point2D player_location, int player_direction)
{
  bool colliding = false;
  switch(player_direction)
  {
    case NORTH :

      if (isInside(player_location.x + (GRID_SIZE * 0.005f) ,player_location.y - (GRID_SIZE * 0.005f))
          && isInside(player_location.x - (GRID_SIZE * 0.005f) ,player_location.y - (GRID_SIZE * 0.005f)))
      {
        colliding = true;
      }
      break;
    case EAST :

      if (isInside(player_location.x + (GRID_SIZE * 0.005f),player_location.y+(GRID_SIZE * 0.005f))
          && isInside(player_location.x + (GRID_SIZE * 0.005f) ,player_location.y - (GRID_SIZE * 0.005f)))
      {
        colliding = true;
      }
      break;

    case SOUTH :

      if (isInside(player_location.x + (GRID_SIZE * 0.005f) ,player_location.y +(GRID_SIZE * 0.005f))
          && isInside(player_location.x - (GRID_SIZE * 0.005f) ,player_location.y + (GRID_SIZE * 0.005f)))
      {
        colliding = true;
      }
      break;
    case WEST :

      if (isInside(player_location.x - (GRID_SIZE * 0.005f) ,player_location.y+(GRID_SIZE * 0.005f))
          && isInside(player_location.x - (GRID_SIZE * 0.005f) ,player_location.y - (GRID_SIZE * 0.005f)))
      {
        colliding = true;
      }
      break;
    default :
      break;
  }


  return colliding;
}

GameObject::~GameObject()
{
}
