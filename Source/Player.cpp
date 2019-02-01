//
// Created by haydn on 20/01/2019.
//

#include <Engine/OGLGame.h>
#include "Player.h"
#include "Constants.h"

Player::Player()
{

  Point2D new_location;
  GameObject new_gameobject(-1, new_location);

  player_gameobject = new_gameobject;
  for (int i =0; i < 15; i++)
  {
    inventory[i].setMyGameObject(new_gameobject);
    inventory[i].setItemName("");
    inventory[i].setItemDescription("");
    inventory[i].setItemID(-1);
  }
  clues_found = nullptr;
  number_clues_found = 0;
  puzzles_solved= nullptr;
  number_puzzles_solved = 0;
  direction = 0;
  moving = false;
  sprite_index = 0;
}
Player::Player(GameObject new_player_gameobject, Item new_inventory[],
int* new_clues_found, int new_number_clues_found,
int* new_puzzles_solved, int new_number_puzzles_solved,
int new_direction, bool new_moving, int new_sprite_index)
{
  player_gameobject = new_player_gameobject;
  for (int i =0; i < 15; i++)
  {
    inventory[i].setMyGameObject(new_inventory[i].getMyGameObject());
    inventory[i].setItemName(new_inventory[i].getItemName());
    inventory[i].setItemDescription(new_inventory[i].getItemDescription());
    inventory[i].setItemID(new_inventory[i].getItemID());
  }
  number_clues_found = new_number_clues_found;
  clues_found = new int[number_clues_found];

  for (int i =0; i < number_clues_found; i++)
  {
    clues_found[i] = new_clues_found[i];
  }
  number_puzzles_solved = new_number_puzzles_solved;
  puzzles_solved = new int[number_puzzles_solved];
  for (int i =0; i < number_puzzles_solved; i++)
  {
    puzzles_solved[i] = new_puzzles_solved[i];
  }
  direction = new_direction;
  moving = new_moving;
  sprite_index = new_sprite_index;

}
GameObject Player::getPlayerGameobject()
{
  return player_gameobject;
}

void Player::setPlayerGameobject(GameObject new_player_gameobject)
{
  player_gameobject = new_player_gameobject;
}

Item Player::getInventory(int index)
{
  return inventory[index];
}
void Player::addToInventory(Item new_item, int index)
{
  inventory[index] = new_item;
}
void Player::addToClues(int new_clue, int index)
{
  int* tmp;
  tmp = new int[number_clues_found];
  for (int i = 0; i < number_clues_found - 1; i++)
  {
    tmp[i]=clues_found[i];

  }
  number_clues_found++;
  clues_found = new int[number_clues_found];
  for (int i = 0; i < number_clues_found - 1; i++)
  {
    clues_found[i]=tmp[i];

  }
  clues_found[index] = new_clue;
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

void Player::savePlayerData()
{
// Select a directory that has write access and exists
  ASGE::FILEIO::setWriteDir(".");
  ASGE::FILEIO::createDir("userdata/");
  ASGE::FILEIO::mount("./userdata/", "userdata");
  ASGE::FILEIO::printFiles("/userdata");

  using Buffer = ASGE::FILEIO::IOBuffer;
  Buffer data = Buffer();
// generate the data buffer that represents a player
  char number[3];
  sprintf(number,"%i", number_clues_found);
  data.append(number, 3);
  for (int i = 0; i < number_clues_found; i++)
  {
    sprintf(number,"%i", clues_found[i]);
    data.append(number, 3);
  }
  sprintf(number,"%i", number_puzzles_solved);
  data.append(number, 3);
  for (int i = 0; i < number_puzzles_solved; i++)
  {
    sprintf(number,"%i", puzzles_solved[i]);
    data.append(number, 3);
  }

  sprintf(number,"%i", direction);
  data.append(number, 3);
  sprintf(number,"%i", moving);
  data.append(number, 3);
  sprintf(number,"%i", sprite_index);
  data.append(number, 3);
  for (int i = 0; i < 15; i++)
  {
    sprintf(number,"%i", inventory[i].getMyGameObject().getMySpriteId());
    data.append(number, 3);
  }
  for (int i = 0; i < 15; i++)
  {
    sprintf(number,"%i", inventory[i].getItemID());
    data.append(number, 3);
  }
  for (int i = 0; i < 15; i++)
  {
    data.append(inventory[i].getItemName());
    data.append(inventory[i].getItemDescription());
  }

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
  if( file.open("/userdata/player.dat" , ASGE::FILEIO::File::IOMode::READ))
  {
    using Buffer = ASGE::FILEIO::IOBuffer;
    Buffer buffer;
    number_clues_found = atoi(buffer.data.get());
    for (int i = 0; i < number_clues_found; i++)
    {
      buffer = file.read();
      file.seek(sizeof(int));
      clues_found[i] =  atoi(buffer.data.get());
    }
    number_puzzles_solved =  atoi(buffer.data.get());
    for (int i = 0; i < number_puzzles_solved; i++)
    {
      buffer = file.read();
      file.seek(sizeof(int));
      puzzles_solved[i] =   atoi(buffer.data.get());
    }

    buffer = file.read();
    file.seek(sizeof(int));
    direction =   atoi(buffer.data.get());
    buffer = file.read();
    file.seek(sizeof(bool));
    moving =  static_cast<bool>( atoi(buffer.data.get()));
    buffer = file.read();
    file.seek(sizeof(int));
    sprite_index =   atoi(buffer.data.get());
    for (int i = 0; i < 15; i++)
    {
      buffer = file.read();
      file.seek(sizeof(int));
      GameObject new_gameobject;
      new_gameobject.setMySpriteId(
          atoi(buffer.as_char()));
      inventory[i].setMyGameObject(new_gameobject);
    }
    for (int i = 0; i < 15; i++)
    {
      buffer = file.read();
      file.seek(sizeof(int));
      inventory[i].setItemID(  atoi(buffer.data.get()));
    }
    file.seek(sizeof(std::string));
    for (int i = 0; i < 15; i++)
    {
      buffer = file.read();
      file.seek(sizeof(std::string));
      inventory[i].setItemName(static_cast<std::string>(buffer.data.get()));
      buffer = file.read();
      inventory[i].setItemDescription(static_cast<std::string>(buffer.data.get()));
    }
  }
  file.close();
}

void Player::movePlayer(double animation_counter)
{
  if (moving)
  {
    if(animation_counter > 0.08)
    {
      switch(direction)
      {
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
      player_gameobject.setMySpriteId(sprite_index);
    }

  }
  else
  {
    switch(direction)
    {
      case NORTH:
          sprite_index = 12;
        break;
      case EAST:
          sprite_index = 8;
        break;
      case SOUTH:
          sprite_index = 0;
        break;
      case WEST:
          sprite_index = 4;
        break;
    }
    player_gameobject.setMySpriteId(sprite_index);

  }
}

void Player::setupPlayer()
{
  clues_found = new int[0];
  direction = SOUTH;
  moving = false;
  number_clues_found = 0;
  number_puzzles_solved = 0;
  puzzles_solved = new int[0];
  sprite_index = 0;
  GameObject new_player_gameobject;
  new_player_gameobject.setMySpriteId(0);
  Point2D new_location;
  new_location.x = GAME_WIDTH / 2 - GRID_SIZE / 2;
  new_location.y = GAME_HEIGHT / 2  - GRID_SIZE / 2;
  new_player_gameobject.setMyLocation(new_location);
  setPlayerGameobject(new_player_gameobject);
  for (int i =0; i < 15; i++)
  {
    GameObject new_gameobject;
    new_gameobject.setMySpriteId(-1);
    inventory[i].setMyGameObject(new_gameobject);
    inventory[i].setItemName("");
    inventory[i].setItemDescription("");
    inventory[i].setItemID(-1);
  }
}