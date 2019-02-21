//
// Created by haydn on 20/01/2019.
//

#include <Engine/OGLGame.h>
#include <cstring>
#include "Player.h"
#include "Constants.h"

/**
*   @brief   Constructor
*   @details This function creates a defualt player class
*   @return  Player
*/
Player::Player()
{

  Point2D new_location;
  GameObject new_gameobject(-1, new_location);

  player_gameobject = new_gameobject;
  int range[15] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
  for (int i : range)
  {
    inventory[i].setMyGameObject(new_gameobject);
    inventory[i].setItemID(-1);
  }
  clues_found = nullptr;
  number_clues_found = 0;
  direction = 0;
  moving = false;
  sprite_index = 0;
}

/**
*   @brief   Get Player Gameobject
*   @details This function returns the player gameobject
*   @return  GameObject
*/
GameObject Player::getPlayerGameobject()
{
  return player_gameobject;
}

/**
*   @brief   Set Player Gameobject
*   @details This function sets the player gameobject
*   @param   new_player_gameobject The player Gameobject
*   @return  void
*/
void Player::setPlayerGameobject(GameObject new_player_gameobject)
{
  player_gameobject = new_player_gameobject;
}

/**
*   @brief   Get Inventory
*   @details This function gets an item from the player Inventory array
*   @param   index The index of the item to return from the array
*   @return  Item
*/
Item Player::getInventory(int index)
{
  return inventory[index];
}

/**
*   @brief   Add Item to Inventory
*   @details This function adds an Item to the player Inventory array
*   @param   new_item The Item to add
*   @param   index The index in the inventory to add the Item
*   @return  void
*/
void Player::addToInventory(Item new_item, int index)
{
  inventory[index] = new_item;
}

/**
*   @brief   Add Clue ID to Clues found array
*   @details This function adds a clue ID to the player Cues found array
*   @param   new_clue The clue ID to add
*   @param   index The index in the Clues found array to add the clue ID
*   @return  void
*/
void Player::addToClues(int new_clue, int index)
{
  int* tmp;
  tmp  = new int[number_clues_found];
    memcpy(tmp, clues_found, number_clues_found * sizeof(int));
  number_clues_found++;
  clues_found = new int[number_clues_found];
    memcpy(clues_found, tmp, number_clues_found * sizeof(int));
  clues_found[index] = new_clue;
}

/**
*   @brief   Get Clues Found array
*   @details This function returns the player Clues found array
*   @return  int*
*/
int* Player::getCluesFound()
{
  return clues_found;
}

/**
*   @brief   Get Clue Found
*   @details This function gets a clue id from the player Clues found array
*   @param   index The index of the clue to return from the array
*   @return  int
*/
int Player::getClueFound(int index)
{
  return clues_found[index];
}

/**
*   @brief   Get Player Direction
*   @details This function returns the player direction
*   @return  int
*/
int Player::getDirection()
{
  return direction;
}

/**
*   @brief   Set Direction
*   @details This function sets the player direction
*   @param   new_direction The direction to set the player
*   @return  void
*/
void Player::setDirection(int new_direction)
{
  direction = new_direction;
}

/**
*   @brief   Get Player moving bool
*   @details This function returns the player moving bool
*   @return  bool
*/
bool Player::isMoving()
{
  return moving;
}

/**
*   @brief   Set Moving
*   @details This function sets the player moving bool
*   @param   new_moving The bool to set the player moving bool to
*   @return  void
*/
void Player::setMoving(bool new_moving)
{
  moving = new_moving;
}

/**
*   @brief   Get Sprite Index
*   @details This function returns the player sprite index
*   @return  int
*/
int Player::getSpriteIndex()
{
  return sprite_index;
}

/**
*   @brief   Get Number Clues Found
*   @details This function returns the number of clues found
*   @return  int
*/
int Player::getNumberCluesFound()
{
  return number_clues_found;
}

/**
*   @brief   Save Player Data
*   @details This function saves the player data
*   @return  void
*/
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
  std::string tmp = std::to_string(direction);
  data.append(tmp);
  tmp =",";
  data.append(tmp);
  tmp = std::to_string(moving);
  data.append(tmp);
  tmp =",";
  data.append(tmp);
  if (sprite_index >= 0 && sprite_index < 10)
  {
    tmp ="0";
    data.append(tmp);
  }
  tmp = std::to_string(sprite_index);
  data.append(tmp);
  tmp =",";
  data.append(tmp);
  int range[15] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
  for (int i : range)
  {
    if (inventory[i].getItemID() >= 0 && inventory[i].getItemID() < 10)
    {
      tmp ="0";
      data.append(tmp);
    }
    tmp = std::to_string(inventory[i].getItemID());
    data.append(tmp);
    tmp =",";
    data.append(tmp);

  }
  for (int i : range)
  {
    if (inventory[i].getMyGameObject().getMySpriteId() >= 0 && inventory[i].getMyGameObject().getMySpriteId() < 10)
    {
      tmp ="0";
      data.append(tmp);
    }
    tmp = std::to_string(inventory[i].getMyGameObject().getMySpriteId());
    data.append(tmp);
    tmp =",";
    data.append(tmp);

  }
  if (number_clues_found >= 0 && number_clues_found < 10)
  {
    tmp ="0";
    data.append(tmp);
  }
  tmp = std::to_string(number_clues_found);
  data.append(tmp);
  tmp =",";
  data.append(tmp);

  if (number_clues_found > 0)
  {
    for (int i = 0; i < number_clues_found; i++)
    {
      if (clues_found[i] >= 0 && clues_found[i] < 10)
      {
        tmp ="0";
        data.append(tmp);
      }
      tmp = std::to_string(clues_found[i]);
      data.append(tmp);
      tmp =",";
      data.append(tmp);
    }
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

/**
*   @brief   Load Player Data
*   @details This function loads the player data
*   @return  void
*/
void Player::loadPlayerData()
{
  using File = ASGE::FILEIO::File;
  File  file = File();

// attempt to open save data file
  if( file.open("/userdata/player.dat" , ASGE::FILEIO::File::IOMode::READ))
  {
    using Buffer = ASGE::FILEIO::IOBuffer;
    size_t length = 2;
    Buffer buffer;
    buffer = file.read();
    direction = std::stoi(buffer.data.get());
    file.seek(length);
    buffer = file.read();
    moving = static_cast<bool>(std::stoi(buffer.data.get()));
    length +=2;
    file.seek(length);
    buffer = file.read();
    sprite_index = (std::stoi(buffer.data.get()));

    int range[15] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    for (int i : range)
    {
      length +=3;
      file.seek(length);
      buffer = file.read();
      inventory[i].setItemID( (std::stoi(buffer.data.get())));
    }
    for (int i : range)
    {
      length +=3;
      file.seek(length);
      buffer = file.read();
      Point2D null;
      inventory[i].setMyGameObject(GameObject((std::stoi(buffer.data.get())),null ));
    }
    length +=3;
    file.seek(length);
    buffer = file.read();
    number_clues_found = (std::stoi(buffer.data.get()));
    if (number_clues_found > 0)
    {
      for (int i = 0; i < number_clues_found; i ++)
      {
        length +=3;
        file.seek(length);
        buffer = file.read();
        addToClues((std::stoi(buffer.data.get())), i);
        number_clues_found--;
      }
    }
  }
  file.close();
}

/**
*   @brief   Move Player
*   @details This function returns the number of clues found
*   @param   animation_counter The current time since the last movement
*   @return  void
*/
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
        default:
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
      default:
        break;
    }
    player_gameobject.setMySpriteId(sprite_index);

  }
}

/**
*   @brief   Setup Player
*   @details This function is used to setup the player
*   @return  void
*/
void Player::setupPlayer()
{
  clues_found = new int[0];
  direction = SOUTH;
  moving = false;
  number_clues_found = 0;
  sprite_index = 0;
  GameObject new_player_gameobject;
  new_player_gameobject.setMySpriteId(0);
  Point2D new_location;
  new_location.x = GAME_WIDTH / 2 - GRID_SIZE / 2;
  new_location.y = GAME_HEIGHT / 2  - GRID_SIZE / 2;
  new_player_gameobject.setMyLocation(new_location);
  setPlayerGameobject(new_player_gameobject);
  int range[15] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
  for (int i : range)
  {
    GameObject new_gameobject;
    new_gameobject.setMySpriteId(-1);
    inventory[i].setMyGameObject(new_gameobject);
    inventory[i].setItemID(-1);
  }
}

bool Player::hasItem(int item_id)
{
  bool has_item = false;
  int range[15] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
  for (int i : range)
  {
    if(inventory[i].getItemID() == item_id)
    {
      has_item = true;
    }
  }
  return has_item;
}