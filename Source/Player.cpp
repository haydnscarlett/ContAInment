//
// Created by haydn on 20/01/2019.
//

#include <Engine/OGLGame.h>
#include "Player.h"
#include "Constants.h"

GameObject Player::getPlayerGameobject()
{
  return player_gameobject;
}

void Player::setPlayerGameobject(GameObject new_player_gameobject)
{
  player_gameobject = new_player_gameobject;
}

ASGE::Sprite* Player::getPlayerSprite(int index)
{
  return player_sprites[index];
}

Item Player::getInventory(int index)
{
  return inventory[index];
}
void Player::addToInventory(Item new_item, int index)
{
  inventory[index] = new_item;
}

int* Player::getCluesFound()
{
  return clues_found;
}

void Player::setCluesFound(int* new_clues_found)
{
  clues_found = new_clues_found;
}

int* Player::getPuzzlesSolved()
{
  return puzzles_solved;
}

void Player::setPuzzlesSolved(int* new_puzzles_solved)
{
  puzzles_solved = new_puzzles_solved;
}

int Player::getDirection()
{
  return direction;
}

void Player::setDirection(int new_direction)
{
  direction = new_direction;
}

bool Player::isMoving()
{
  return moving;
}

void Player::setMoving(bool new_moving)
{
  moving = new_moving;
}

int Player::getSpriteIndex()
{
  return sprite_index;
}

void Player::setSpriteIndex(int new_sprite_index)
{
  sprite_index = new_sprite_index;
}

int Player::getNumberCluesFound()
{
  return number_clues_found;
}

void Player::setNumberCluesFound(int new_number_clues_found)
{
  number_clues_found = new_number_clues_found;
}

int Player::getNumberPuzzlesSolved()
{
  return number_puzzles_solved;
}

void Player::setNumberPuzzlesSolved(int new_number_puzzles_solved)
{
  number_puzzles_solved = new_number_puzzles_solved;
}

void Player::setPlayerSprites(ASGE::Sprite* new_player_sprites[])
{
  for (int i = 0; i < 16; i++)
  {
    player_sprites[i] = new_player_sprites[i];
  }

}


void Player::savePlayerData()
{
  using Buffer = ASGE::FILEIO::IOBuffer;
  Buffer data = Buffer();
// generate the data buffer that represents a player
  for (int i = 0; i < 15; i++)
  {
    data.append(inventory[i].getMyGameObject().getMyLocation().x);
    data.append(inventory[i].getMyGameObject().getMyLocation().y);
    data.append(inventory[i].getItemName());
    data.append(inventory[i].getItemDescription());
    data.append(inventory[i].getItemID());
  }
  data.append(number_clues_found);
  for (int i = 0; i < number_clues_found; i++)
  {
    data.append(clues_found[i]);
  }
  data.append(number_puzzles_solved);
  for (int i = 0; i < number_puzzles_solved; i++)
  {
    data.append(puzzles_solved[i]);
  }

  data.append(direction);
  data.append(moving);
  data.append(sprite_index);

  using File = ASGE::FILEIO::File;
  File player_data = File();
// open the file in write mode
  if(player_data.open( "/userdata/player.dat",
                     ASGE::FILEIO::File::IOMode::WRITE))
  {
    // write the buffer to the file
    player_data.write(data);
  }

  player_data.close();
}

void Player::loadPlayerData()
{
  using File = ASGE::FILEIO::File;
  File  file = File();

// attempt to open save data file
  if( file.open("/data/userdata/player_data.dat"))
  {
    using Buffer = ASGE::FILEIO::IOBuffer;
    Buffer buffer = file.read();

  }
}

void Player::movePlayer(double animation_counter)
{
  if (moving)
  {
    if(animation_counter > 0.08)
    {
      switch(direction)
      {
        case SOUTH:
          if (sprite_index + 1 > 3 ||
              sprite_index + 1 < 0)
          {
            sprite_index = 0;
          }
          else
          {
            sprite_index += 1;
          }
          break;
        case EAST:
          if (sprite_index + 1 > 11 ||
              sprite_index + 1 < 8)
          {
            sprite_index = 8;
          }
          else
          {
            sprite_index += 1;
          }
          break;
        case NORTH:
          if (sprite_index + 1 > 15 ||
              sprite_index + 1 < 12)
          {
            sprite_index = 12;
          }
          else
          {
            sprite_index += 1;
          }
          break;
        case WEST:
          if (sprite_index + 1 > 7||
              sprite_index + 1 < 4)
          {
            sprite_index = 4;
          }
          else
          {
            sprite_index += 1;
          }
          break;
      }
      player_gameobject.setMySprite(player_sprites[sprite_index]);
    }

  }
  else
  {
    if (sprite_index > 0 && sprite_index < 4)
    {
      sprite_index = 0;
      player_gameobject.setMySprite(player_sprites[sprite_index]);
    }
    else if (sprite_index > 4 && sprite_index < 8)
    {
      sprite_index = 4;
      player_gameobject.setMySprite(player_sprites[sprite_index]);
    }
    else if (sprite_index > 8 && sprite_index < 12)
    {
      sprite_index = 8;
      player_gameobject.setMySprite(player_sprites[sprite_index]);
    }
    else if (sprite_index > 12 && sprite_index < 16)
    {
      sprite_index = 12;
      player_gameobject.setMySprite(player_sprites[sprite_index]);
    }
  }
}

void Player::setupPlayer(ASGE::Sprite* new_sprites[])
{
  clues_found = new int[0];
  direction = SOUTH;
  moving = false;
  number_clues_found = 0;
  number_puzzles_solved = 0;
  puzzles_solved = new int[0];
  sprite_index = 0;
  setPlayerSprites(new_sprites);
  GameObject new_player_gameobject;
  new_player_gameobject.setMySprite(new_sprites[0]);
  Point2D new_location;
  new_location.x = new_sprites[0]->xPos();
  new_location.y = new_sprites[0]->yPos();
  new_player_gameobject.setMyLocation(new_location);
  setPlayerGameobject(new_player_gameobject);
  for (int i =0; i < 15; i++)
  {
    GameObject new_gameobject;

    inventory[i].setMyGameObject(new_gameobject);
    inventory[i].setItemName("");
    inventory[i].setItemDescription("");
    inventory[i].setItemID(-1);
  }
}