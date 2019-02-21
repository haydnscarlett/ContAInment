//
// Created by haydn on 20/01/2019.
//

#include <soloud.h>
#include "Room.h"

#include "Constants.h"

/**
*   @brief   Get My Background
*   @details This function returns the Room's Background array
*   @return  GameObject*
*/
GameObject* Room::getMyBackground()
{
  return my_background;
}

/**
*   @brief   Set My Background
*   @details This function sets the Room's Background array
*   @param   new_background The Background array
*   @return  void
*/
void Room::setMyBackground(GameObject* new_background)
{
  my_background = new_background;
}

/**
*   @brief   Get My Foreground
*   @details This function returns the Room's Foreground array
*   @return  GameObject*
*/
GameObject* Room::getMyForeground()
{
  return my_foreground;
}

/**
*   @brief   Set My Foreground
*   @details This function sets the Room's Foreground array
*   @param   new_foreground The Foreground array
*   @return  void
*/
void Room::setMyForeground(GameObject* new_foreground)
{
  my_foreground = new_foreground;
}

/**
*   @brief   Get My Walls
*   @details This function returns the Room's Walls array
*   @return  GameObject*
*/
GameObject* Room::getMyWalls()
{
  return my_walls;
}

/**
*   @brief   Get My Clues
*   @details This function returns the Room's Clues array
*   @return  Clue*
*/
Clue* Room::getMyClues()
{
  return my_clues;
}

/**
*   @brief   Set My Clues
*   @details This function sets the Room's Clues array
*   @param   new_clues The Clues array
*   @return  void
*/
void Room::setMyClues(Clue* new_clues)
{
  my_clues = new_clues;
}

/**
*   @brief   Get My Items
*   @details This function returns the Room's Items array
*   @return  Item*
*/
Item* Room::getMyItems()
{
  return my_items;
}

/**
*   @brief   Set My Items
*   @details This function sets the Room's Items array
*   @param   new_items The Items array
*   @return  void
*/
void Room::setMyItems(Item* new_items)
{
  my_items = new_items;
}

/**
*   @brief   Get My Puzzle
*   @details This function returns the Room's Puzzle
*   @return  Puzzle
*/
 Puzzle Room::getMyPuzzle()
{
  return my_puzzle;
}

/**
*   @brief   Set My Puzzle
*   @details This function sets the Room's Puzzle
*   @param   new_puzzle The Puzzle
*   @return  void
*/
void Room::setMyPuzzle(const Puzzle &new_puzzle)
{
  my_puzzle = new_puzzle;
}

/**
*   @brief   Get Room ID
*   @details This function returns the Room's ID
*   @return  int
*/
int Room::getRoomID()
{
  return room_id;
}

/**
*   @brief   Set Room ID
*   @details This function sets the Room's ID
*   @param   new_id The Room id
*   @return  void
*/
void Room::setRoomID(int new_id)
{
  room_id = new_id;
}

/**
*   @brief   Get My Exits
*   @details This function returns the Room's Exits array
*   @return  Exit*
*/
Exit* Room::getMyExits()
{
  return my_exits;
}

/**
*   @brief   Set My Exits
*   @details This function sets the Room's Exits array
*   @param   new_exits The Exits array
*   @return  void
*/
void Room::setMyExits(Exit* new_exits)
{
  my_exits = new_exits;
}

/**
*   @brief   Get My Gridsize X
*   @details This function returns the Room's X Gridsize
*   @return  int
*/
int Room::getMyGridsizeX()
{
  return my_gridsize_x;
}

/**
*   @brief   Set My Gridsize X
*   @details This function sets the Room's X Gridsize
*   @param   new_gridsize_x The Room's X Gridsize
*   @return  void
*/
void Room::setMyGridsizeX(int new_gridsize_x)
{
  my_gridsize_x = new_gridsize_x;
}

/**
*   @brief   Get My Gridsize Y
*   @details This function returns the Room's Y Gridsize
*   @return  int
*/
int Room::getMyGridsizeY()
{
  return my_gridsize_y;
}

/**
*   @brief   Set My Gridsize Y
*   @details This function sets the Room's Y Gridsize
*   @param   new_gridsize_y The Room's Y Gridsize
*   @return  void
*/
void Room::setMyGridsizeY(int new_gridsize_y)
{
  my_gridsize_y = new_gridsize_y;
}

/**
*   @brief   Get Number Clues
*   @details This function returns the Room's number of clues
*   @return  int
*/
int Room::getNumberClues() const
{
  return number_of_clues;
}

/**
*   @brief   Set Number Clues
*   @details This function sets the Room's Number of Clues
*   @param   new_number_of_clues The Number of Clues
*   @return  void
*/
void Room::setNumberClues(int new_number_of_clues)
{
  number_of_clues = new_number_of_clues;
}

/**
*   @brief   Get Number Items
*   @details This function returns the Room's number of Items
*   @return  int
*/
int Room::getNumberItems() const
{
  return number_of_items;
}

/**
*   @brief   Set Number Items
*   @details This function sets the Room's Number of Items
*   @param   new_number_of_items The Number of Items
*   @return  void
*/
void Room::setNumberItems(int new_number_of_items)
{
  number_of_items = new_number_of_items;
}

/**
*   @brief   Get Number Exits
*   @details This function returns the Room's number of Exits
*   @return  int
*/
int Room::getNumberExits() const
{
  return number_of_exits;
}

/**
*   @brief   Set Number Exits
*   @details This function sets the Room's Number of Exits
*   @param   new_number_of_exits The Number of Exits
*   @return  void
*/
void Room::setNumberExits(int new_number_of_exits)
{
  number_of_exits = new_number_of_exits;
}

/**
*   @brief   Remove Item
*   @details This function Removes an Item from the room
*   @param   item_ID The Item id
*   @return  void
*/
void Room::removeItem(int item_ID)
{
  auto* temp = new Item[number_of_items];
  bool item_removed = false;
  for (int i = 0; i < number_of_items - 1; i++)
  {
    if(item_ID != my_items[i].getItemID())
    {
      if(item_removed)
      {
        temp[i] =  my_items[i + 1];
      }
      else
      {
        temp[i] =  my_items[i];
      }
    }
    else
    {
      temp[i] =  my_items[i + 1];
      item_removed = true;
    }
  }
  number_of_items--;
  my_items = new Item[number_of_items];
  for (int i = 0; i < number_of_items; i++)
  {
    my_items[i] = temp[i];
  }
}

/**
*   @brief   Add Item
*   @details This function Adds an Item to the room
*   @param   new_item The Item
*   @return  void
*/
void Room::addItem(Item new_item)
{
  auto* tmp = my_items;
  number_of_items++;
  my_items = new Item[number_of_items];
  for(int i = 0; i < number_of_items - 1; i++)
  {
    my_items[i] = tmp[i];
  }
  my_items[number_of_items - 1] = new_item;
  tmp = nullptr;
  delete tmp;
}

/**
*   @brief   Move Room
*   @details This function moves the room relative to the player
*   @param   player The Player
*   @return  void
*/
void Room::moveRoom(Player* player)
{
  if (player->isMoving())
  {
    for (int i = 0; i < (my_gridsize_x * my_gridsize_y); i++)
    {
      Point2D new_location = my_background[i].getMyLocation();
      switch(player->getDirection())
      {
        case SOUTH :
          new_location.y -= GRID_SIZE * MOVEMENT_DISTANCE;
          break;
        case WEST :
          new_location.x += GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        case NORTH :
          new_location.y += GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        case EAST :
          new_location.x -= GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        default :
          break;
      }
      my_background[i].setMyLocation(new_location);
    }

    for (int i = 0; i < (((my_gridsize_x + my_gridsize_y) * 2) + 4); i++)
    {
      Point2D new_location = my_walls[i].getMyLocation();
      switch(player->getDirection())
      {
        case SOUTH :
          new_location.y -= GRID_SIZE * MOVEMENT_DISTANCE;
          break;
        case WEST :
          new_location.x += GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        case NORTH :
          new_location.y += GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        case EAST :
          new_location.x -= GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        default :
          break;
      }
      my_walls[i].setMyLocation(new_location);
    }
    for (int i = 0; i < (my_gridsize_x * my_gridsize_y); i++)
    {
      if(my_foreground[i].getMySpriteId() != -1)
      {
        Point2D new_location = my_foreground[i].getMyLocation();
        switch(player->getDirection())
        {
          case SOUTH :
            new_location.y -= GRID_SIZE* MOVEMENT_DISTANCE;
            break;
          case WEST :
            new_location.x += GRID_SIZE* MOVEMENT_DISTANCE;
            break;
          case NORTH :
            new_location.y += GRID_SIZE* MOVEMENT_DISTANCE;
            break;
          case EAST :
            new_location.x -= GRID_SIZE* MOVEMENT_DISTANCE;
            break;
          default :
            break;
        }
        my_foreground[i].setMyLocation(new_location);
      }
    }
    for (int i = 0; i < number_of_clues; i++)
    {
      Point2D new_location = my_clues[i].getMyGameObject().getMyLocation();
      switch(player->getDirection())
      {
        case SOUTH :
          new_location.y -= GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        case WEST :
          new_location.x += GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        case NORTH :
          new_location.y += GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        case EAST :
          new_location.x -= GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        default :
          break;
      }
      my_clues[i].setMyGameObject(GameObject(my_clues[i].getMyGameObject().getMySpriteId(),new_location));
    }
    for (int i = 0; i < number_of_items; i++)
    {
      Point2D new_location = my_items[i].getMyGameObject().getMyLocation();
      switch(player->getDirection())
      {
        case SOUTH :
          new_location.y -= GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        case WEST :
          new_location.x += GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        case NORTH :
          new_location.y += GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        case EAST :
          new_location.x -= GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        default :
          break;
      }
        my_items[i].setMyGameObject(GameObject(my_items[i].getMyGameObject().getMySpriteId(),new_location));
    }
    for (int i = 0; i < my_puzzle.getNumberSwitches(); i++)
    {
      Point2D new_location = my_puzzle.getMySwitches()[i].getMyOnGameobject().getMyLocation();
      switch(player->getDirection())
      {
        case SOUTH :
          new_location.y -= GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        case WEST :
          new_location.x += GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        case NORTH :
          new_location.y += GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        case EAST :
          new_location.x -= GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        default :
          break;
      }
        my_puzzle.getMySwitches()[i].setMyOffGameobject(GameObject(my_puzzle.getMySwitches()[i].getMyOffGameobject().
        getMySpriteId(),new_location));
        my_puzzle.getMySwitches()[i].setMyOnGameobject(GameObject(my_puzzle.getMySwitches()[i].getMyOnGameobject().
                getMySpriteId(),new_location));
    }
    for (int i = 0; i < my_puzzle.getNumberMovables(); i++)
    {
      if(!my_puzzle.getMyMovables()[i].collisionCheck(
          player->getPlayerGameobject().getMyLocation(),
          player->getDirection(), false))
      {
        Point2D new_location = my_puzzle.getMyMovables()[i].getMyLocation();
        Point2D* new_target_locations = my_puzzle.getTargetMovableLocations();
        Point2D new_target_location = new_target_locations[i];
        switch(player->getDirection())
        {
          case SOUTH :
            new_location.y -= GRID_SIZE* MOVEMENT_DISTANCE;
            new_target_location.y -= GRID_SIZE* MOVEMENT_DISTANCE;
            break;
          case WEST :
            new_location.x += GRID_SIZE* MOVEMENT_DISTANCE;
            new_target_location.x += GRID_SIZE* MOVEMENT_DISTANCE;
            break;
          case NORTH :
            new_location.y += GRID_SIZE* MOVEMENT_DISTANCE;
            new_target_location.y += GRID_SIZE* MOVEMENT_DISTANCE;
            break;
          case EAST :
            new_location.x -= GRID_SIZE* MOVEMENT_DISTANCE;
            new_target_location.x -= GRID_SIZE* MOVEMENT_DISTANCE;
            break;
          default :
            break;
        }
        my_puzzle.getMyMovables()[i].setMyLocation(new_location);
        new_target_locations[i] = new_target_location;
        my_puzzle.setTargetMovableLocations(new_target_locations);
      }
      else
      {
        Point2D* new_target_locations = my_puzzle.getTargetMovableLocations();
        Point2D new_target_location = new_target_locations[i];
        switch(player->getDirection())
        {
          case SOUTH :
            new_target_location.y -= GRID_SIZE* MOVEMENT_DISTANCE;
            break;
          case WEST :
            new_target_location.x += GRID_SIZE* MOVEMENT_DISTANCE;
            break;
          case NORTH :
            new_target_location.y += GRID_SIZE* MOVEMENT_DISTANCE;
            break;
          case EAST :
            new_target_location.x -= GRID_SIZE* MOVEMENT_DISTANCE;
            break;
          default :
            break;
        }
        new_target_locations[i] = new_target_location;
        my_puzzle.setTargetMovableLocations(new_target_locations);
      }
    }
    for (int i = 0; i < number_of_exits; i++)
    {
      Point2D new_location = my_exits[i].getMyExitGameobject().getMyLocation();
      switch(player->getDirection())
      {
        case NORTH :
          new_location.y += GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        case EAST :
          new_location.x -= GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        case SOUTH :
          new_location.y -= GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        case WEST :
          new_location.x += GRID_SIZE* MOVEMENT_DISTANCE;
          break;
        default :
          break;
      }
        my_exits[i].setMyExitGameobject(GameObject(my_exits[i].getMyExitGameobject().getMySpriteId(),new_location));
    }
  }
}

/**
*   @brief   Check Collisions
*   @details This function Checks Collisions with the player
*   @param   player The Player to check
*   @param   add_item_check The whether to double the distance or not
*   @return  bool Whether the player is colliding with an object in the
*            room that will stop them moving
*/
bool Room::checkCollisions(Player* player, bool add_item_check)
{
  bool colliding = false;

  for (int i = 0; i < (my_gridsize_x * my_gridsize_y); i++)
  {
    if(my_foreground[i].collisionCheck(
        player->getPlayerGameobject().getMyLocation(), player->getDirection(),
        add_item_check))
    {
      colliding = true;
    }
  }
  for (int i = 0; i < (((my_gridsize_x + my_gridsize_y) * 2) + 4); i++)
  {
    if(my_walls[i].collisionCheck(
        player->getPlayerGameobject().getMyLocation(), player->getDirection(),
        add_item_check))
    {
      colliding = true;
    }
  }
  for (int i = 0; i < number_of_clues; i++)
  {
    if(my_clues[i].getMyGameObject().collisionCheck(
        player->getPlayerGameobject().getMyLocation(), player->getDirection(),
        add_item_check))
    {
      colliding = true;
    }
  }
  for (int i = 0; i < number_of_items; i++)
  {
    if(my_items[i].getMyGameObject().collisionCheck(
        player->getPlayerGameobject().getMyLocation(), player->getDirection(),
        add_item_check))
    {
      colliding = true;
    }
  }
  for (int i = 0; i < my_puzzle.getNumberSwitches(); i++)
  {
    if(my_puzzle.getMySwitches()[i].getMyOnGameobject().collisionCheck(
        player->getPlayerGameobject().getMyLocation(), player->getDirection(),
        add_item_check))
    {
      colliding = true;
    }
  }
  return colliding;
}

/**
*   @brief   Check For Interactables
*   @details This function Check Collisions with the player
*   @param   player The Player to check
*   @param   text_to_display The text to display in th text box
*   @param   power_on The state of the facilities power
*   @return  bool Whether the player is interacting with an object in the
*            room
*/
int Room::checkForInteractables(Player* player, std::string* text_to_display,
                                 bool* power_on )
{
  int colliding = false;

  for (int i = 0; i < number_of_clues; i++)
  {
    if(my_clues[i].getMyGameObject().collisionCheck(
        player->getPlayerGameobject().getMyLocation(), player->getDirection(),
        false))
    {
       if(my_clues[i].addClueToPlayer(player->getCluesFound(),
                                     player->getNumberCluesFound()))
      {
        player->addToClues(my_clues[i].getClueID(), player->getNumberCluesFound());
      }
      switch(my_clues[i].getClueID())
      {
        case 0:
          *text_to_display = "There is no power.";
          break;
        case 1:
          *text_to_display = "There is a spare reactor fuse in the lab coat in the garden, did you leave \n"
                             "it there on purpose?";
          break;
        case 2:
          *text_to_display = "8197";
          break;
        case 3:
          *text_to_display = "IMPORTANT: In case of an Emergency password is 'SANE'";
          break;
        case 4:
          *text_to_display = "Hey hun, waiting at the reception ;)";
          break;
        case 5:
          *text_to_display = "Reading list: Reprogrammimng the brain, Modern Neuroscience  \n"
                             "Advanced AI, AI Pattern Recogniton, Printing Synthetic organs, The synthetic Human.";
          break;
        case 6:
          *text_to_display = "This has been used recently, could it be? FIBI?";
          break;
        case 7:
          *text_to_display = "What is this? We were using human brains, \nno no no, this cannot be happening!";
          break;
        case 8:
          *text_to_display = "Power continues to cut out, i'm starting to think it's not a coincidence, \n"
                             "i'll keep the key to the reactor in my safe until the issue is resolved.";
          break;
        case 9:
          *text_to_display = "Keycards: Red = Emergency exit from Atrium, Green = Waste Disposal, \n"
                             "Yellow = Labs, Blue = Reception Exit";
          break;
        case 10:
          *text_to_display =  "10101 for power";
          break;
        default:
          break;
      }
      colliding = 1;
    }
  }
  bool item_added = false;
  for (int i = 0; i < number_of_items; i++)
  {
    if(my_items[i].getMyGameObject().collisionCheck(
        player->getPlayerGameobject().getMyLocation(), player->getDirection(),
        false))
    {
      for (int j = 0; j < 15; j ++)
      {
         if (player->getInventory(j).getItemID() == -1 && !item_added)
        {
          if(my_items[i].getItemID() == 7)
          {
            for(int k = 0; k < player->getNumberCluesFound(); k++)
            {
              if (player->getClueFound(k) == 2)
              {
                Item new_item = my_items[i].addItemToInventory();
                switch(my_items[i].getItemID())
                {
                  case 0:
                    *text_to_display = "You found a screwdriver.";
                    break;
                  case 1:
                    *text_to_display = "You found a fuse.";
                    break;
                  case 2:
                    *text_to_display = "You found a yellow keycard.";
                    break;
                  case 3:
                    *text_to_display = "You found a blue keycard.";
                    break;
                  case 4:
                    *text_to_display = "You found a can.";
                    break;
                  case 5:
                    *text_to_display = "You found a lunch box.";
                    break;
                  case 6:
                    *text_to_display = "You found a can.";
                    break;
                  case 7:
                    *text_to_display = "You found a key to the reactor room.";
                    break;
                  case 8:
                    *text_to_display = "You found a hammer.";
                    break;
                  case 9:
                    *text_to_display = "You found a pair of pliers.";
                    break;
                  case 10:
                    *text_to_display = "You found a red keycard.";
                    break;
                  case 11:
                    *text_to_display = "You found a green keycard.";
                    break;
                  case 12:
                    *text_to_display = "You found a Magnifying Glass.";
                    break;
                  default:
                    break;
                }
                player->addToInventory(new_item, j);
                removeItem(my_items[i].getItemID());
                j = 15;
                i = number_of_items;
                item_added = true;
                colliding = 1;
              }
            }
            if (!item_added)
            {
              *text_to_display = "You do not know the code.";
              colliding = 1;
            }

          }
          else
          {
            Item new_item = my_items[i].addItemToInventory();
            switch(my_items[i].getItemID())
            {
              case 0:
                *text_to_display = "You found a screwdriver.";
                break;
              case 1:
                *text_to_display = "You found a fuse.";
                break;
              case 2:
                *text_to_display = "You found a yellow keycard.";
                break;
              case 3:
                *text_to_display = "You found a blue keycard.";
                break;
              case 4:
                *text_to_display = "You found a can.";
                break;
              case 5:
                *text_to_display = "You found a lunch box.";
                break;
              case 6:
                *text_to_display = "You found a can.";
                break;
              case 7:
                *text_to_display = "You found a key to the reactor room.";
                break;
              case 8:
                *text_to_display = "You found a hammer.";
                break;
              case 9:
                *text_to_display = "You found a pair of pliers.";
                break;
              case 10:
                *text_to_display = "You found a red keycard.";
                break;
              case 11:
                *text_to_display = "You found a green keycard.";
                break;
              case 12:
                *text_to_display = "You found a Magnifying Glass.";
                break;
              default:
                break;
            }
            player->addToInventory(new_item, j);
            removeItem(my_items[i].getItemID());
            j = 15;
            i = number_of_items;
            item_added = true;
            colliding = 1;
          }
        }
        if (j == 14 && !item_added && !colliding)
        {
          *text_to_display = "Inventory full. Please drop something first.";
          colliding = 1;
        }

      }
    }
  }
  for (int i = 0; i < my_puzzle.getNumberSwitches(); i++)
  {
    if(my_puzzle.getMySwitches()[i].getMyOnGameobject().collisionCheck(
        player->getPlayerGameobject().getMyLocation(), player->getDirection(),
        false))
    {
      my_puzzle.getMySwitches()[i].setOn(!my_puzzle.getMySwitches()[i].isOn());

      colliding = 2;
    }
  }
   if(my_puzzle.checkPuzzleCompleted(player, power_on) && !*power_on &&
      room_id == REACTOR)
  {
    *power_on = true;
    *text_to_display = my_puzzle.getPuzzleSolvedMessage();
    colliding = 1;
  }
  return colliding;
}

/**
*   @brief   Reset Room Position
*   @details This function Resets the Room's Position relative to the distance
 *            of the player to the exit they are entering the room for
*   @param   distance The distance to move the rooms game objects
*   @return  void
*/
void Room::resetRoomPosition(Point2D distance)
{
  for (int i = 0; i < (my_gridsize_x * my_gridsize_y); i++)
  {
    Point2D new_location = my_background[i].getMyLocation();
    new_location.x += distance.x;
    new_location.y += distance.y;
    my_background[i].setMyLocation(new_location);
  }

  for (int i = 0; i < (((my_gridsize_x + my_gridsize_y) * 2) + 4); i++)
  {
    Point2D new_location = my_walls[i].getMyLocation();
    new_location.x += distance.x;
    new_location.y += distance.y;
    my_walls[i].setMyLocation(new_location);
  }

  for (int i = 0; i < (my_gridsize_x * my_gridsize_y); i++)
  {
    if(my_foreground[i].getMySpriteId() != -1)
    {
      Point2D new_location = my_foreground[i].getMyLocation();
      new_location.x += distance.x;
      new_location.y += distance.y;
      my_foreground[i].setMyLocation(new_location);

    }
  }
  for (int i = 0; i < number_of_clues; i++)
  {
    Point2D new_location = my_clues[i].getMyGameObject().getMyLocation();
    new_location.x += distance.x;
    new_location.y += distance.y;
    my_clues[i].setMyGameObject(GameObject(my_clues[i].getMyGameObject().getMySpriteId(),new_location));
  }
  for (int i = 0; i < number_of_items; i++)
  {
      Point2D new_location = my_items[i].getMyGameObject().getMyLocation();
      new_location.x += distance.x;
      new_location.y += distance.y;
      my_items[i].setMyGameObject(GameObject(my_items[i].getMyGameObject().getMySpriteId(),new_location));
  }
  for (int i = 0; i < my_puzzle.getNumberSwitches(); i++)
  {
      Point2D new_location = my_puzzle.getMySwitches()[i].getMyOnGameobject().getMyLocation();
    new_location.x += distance.x;
    new_location.y += distance.y;
      my_puzzle.getMySwitches()[i].setMyOffGameobject(GameObject(my_puzzle.getMySwitches()[i].getMyOffGameobject().
              getMySpriteId(),new_location));
      my_puzzle.getMySwitches()[i].setMyOnGameobject(GameObject(my_puzzle.getMySwitches()[i].getMyOnGameobject().
              getMySpriteId(),new_location));
  }
  for (int i = 0; i < my_puzzle.getNumberMovables(); i++)
  {
    Point2D new_location = my_puzzle.getMyMovables()[i].getMyLocation();
    Point2D* new_target_locations = my_puzzle.getTargetMovableLocations();
    new_location.x += distance.x;
    new_location.y += distance.y;
    new_target_locations[i].x += distance.x;
    new_target_locations[i].y += distance.y;
      my_puzzle.getMyMovables()[i].setMyLocation(new_location);
    my_puzzle.setTargetMovableLocations(new_target_locations);
  }

  for (int i = 0; i < number_of_exits; i++)
  {
    Point2D new_location = my_exits[i].getMyExitGameobject().getMyLocation();
    new_location.x += distance.x;
    new_location.y += distance.y;
      my_exits[i].setMyExitGameobject(GameObject(my_exits[i].getMyExitGameobject().getMySpriteId(),new_location));
  }
}

/**
*   @brief   Check Exits
*   @details This function checks to see if a player is colliding with an exit
 *            and updates the game accordingly
*   @param   player The Player to check
*   @param   text_to_display The text to display in th text box
*   @param   game_state The state of game
*   @param   power_on The state of the facilties power
*   @param   exit_check The exit check array
*   @return  void
*/
void Room::checkExits(Player* player, std::string* text_to_display,
                int* game_state, bool power_on, int* exit_check)
{
  exit_check[0] = 0;
  exit_check[1] = 0;
  exit_check[2] = 0;

  for (int i = 0; i < number_of_exits; i++)
  {
    if (my_exits[i].isLocked())
    {
      if(my_exits[i].getMyExitGameobject().collisionCheck(
          player->getPlayerGameobject().getMyLocation(), player->getDirection(),
          false))
      {
        if(my_puzzle.checkPuzzleCompleted(player, &power_on))
        {
          for (int j =0; j < my_puzzle.getNumberLinkedExits(); j++)
          {
            for(int k =0; k < number_of_exits; k++)
            {

              if (my_puzzle.getLinkedExits()[j] == my_exits[i].getExitID())
              {
                my_exits[i].setLocked(false);
              }
            }
          }
          *text_to_display = my_puzzle.getPuzzleSolvedMessage();
          *game_state = TEXT_DISPLAY;
          exit_check[0] = 2;
          exit_check[1] = my_exits[i].getConnectedRoomID();
          exit_check[2] = my_exits[i].getConnectedExitID();
          return ;
        }
        else
        {
          *text_to_display = "It's Locked!";
          *game_state = TEXT_DISPLAY;
          player->setDirection(player->getDirection() - 2);
          if(player->getDirection() < 0)
          {

            player->setDirection(player->getDirection() + 4);
          }
          exit_check[0] = 1;
          exit_check[1] = 0;
          exit_check[2] = 0;
          return ;
        }
      }
    }
    else
    {
      if(my_exits[i].getMyExitGameobject().collisionCheck(
          player->getPlayerGameobject().getMyLocation(), player->getDirection(),
          false))
      {
        exit_check[0] = 2;
        exit_check[1] = my_exits[i].getConnectedRoomID();
        exit_check[2] = my_exits[i].getConnectedExitID();
        return ;
      }
    }
  }
}

/**
*   @brief   Check Movable Collisions
*   @details This function Checks Movable Collisions with the player
*   @param   player The Player to check
*   @param   add_item_check The whether to double the distance or not
*   @return  bool Whether the player is colliding with an object in the
*            room that will stop them moving
*/
bool Room::checkMovableCollisions(Player* player, bool add_item_check)
{
  for (int i = 0; i < my_puzzle.getNumberMovables(); i++)
  {
    int direction = player->getDirection();
    direction += 2;
    if (direction > 3)
    {
      direction -= 4;
    }
    if(my_puzzle.getMyMovables()[i].collisionCheck(
        player->getPlayerGameobject().getMyLocation(), player->getDirection(),
        true))
    {
     return checkCollisions(player, add_item_check);
    }
  }
  return false;
}


/**
*   @brief   Save room Data
*   @details This function saves the room data
*   @return  void
*/
void Room::saveRoom()
{
// Select a directory that has write access and exists
  ASGE::FILEIO::setWriteDir(".");
  ASGE::FILEIO::createDir("userdata/");
  ASGE::FILEIO::mount("./userdata/", "userdata");
  ASGE::FILEIO::printFiles("/userdata");
  std::string tmp;
  using Buffer = ASGE::FILEIO::IOBuffer;
  Buffer data = Buffer();
// generate the data buffer that represents a room
  tmp = std::to_string(my_background[0].getMyLocation().x);
  if (my_background[0].getMyLocation().x  < -100.f)
  {
    tmp ="11";
    data.append(tmp);
  }
  else if (my_background[0].getMyLocation().x  < -10.f)
  {
    tmp ="10";
    data.append(tmp);
  }
  else if (my_background[0].getMyLocation().x  < 0.f)
  {
    tmp ="09";
    data.append(tmp);
  }
  else if (my_background[0].getMyLocation().x  < 10.f)
  {
    tmp ="08";
    data.append(tmp);
  }
  else if (my_background[0].getMyLocation().x  < 100.f)
  {
    tmp ="09";
    data.append(tmp);
  }
  else if (my_background[0].getMyLocation().x  < 1000.f)
  {
    tmp ="10";
    data.append(tmp);
  }
  tmp =",";
  data.append(tmp);
  tmp = std::to_string(my_background[0].getMyLocation().x);
  data.append(tmp);
  tmp =",";
  data.append(tmp);
  tmp = std::to_string(my_background[0].getMyLocation().y);
  if (my_background[0].getMyLocation().y  < -100.f)
  {
    tmp ="11";
    data.append(tmp);
  }
  else if (my_background[0].getMyLocation().y  < -10.f)
  {
    tmp ="10";
    data.append(tmp);
  }
  else if (my_background[0].getMyLocation().y  < 0.f)
  {
    tmp ="09";
    data.append(tmp);
  }
  else
  if (my_background[0].getMyLocation().y  < 10.f)
  {
    tmp ="08";
    data.append(tmp);
  }
  else if (my_background[0].getMyLocation().y  < 100.f)
  {
    tmp ="09";
    data.append(tmp);
  }
  else if (my_background[0].getMyLocation().y  < 1000.f)
  {
    tmp ="10";
    data.append(tmp);
  }
  tmp =",";
  data.append(tmp);
  tmp = std::to_string(my_background[0].getMyLocation().y);
  data.append(tmp);
  tmp =",";
  data.append(tmp);
  if (number_of_items >= 0 && number_of_items < 10)
  {
    tmp ="0";
    data.append(tmp);
  }
  tmp = std::to_string(number_of_items);
  data.append(tmp);
  tmp =",";
  data.append(tmp);

  if (number_of_items > 0)
  {
    for (int i = 0; i < number_of_items; i++)
    {
      if (my_items[i].getItemID() >= 0 && my_items[i].getItemID() < 10)
      {
        tmp ="0";
        data.append(tmp);
      }
      tmp = std::to_string(my_items[i].getItemID());
      data.append(tmp);
      tmp =",";
      data.append(tmp);
    }
    for (int i = 0; i < number_of_items; i++)
    {
      if (my_items[i].getMyGameObject().getMySpriteId() >= 0 &&
          my_items[i].getMyGameObject().getMySpriteId()  < 10)
      {
        tmp ="0";
        data.append(tmp);
      }
      tmp = std::to_string(my_items[i].getMyGameObject().getMySpriteId() );
      data.append(tmp);
      tmp =",";
      data.append(tmp);
    }
    for (int i = 0; i < number_of_items; i++)
    {
      tmp = std::to_string(my_items[i].getMyGameObject().getMyLocation().x);
      if (tmp.compare("") >= 0 && tmp.compare("")  < 10)
      {
        tmp ="0";
        data.append(tmp);
        tmp = std::to_string(my_items[i].getMyGameObject().getMyLocation().x);
      }
      tmp = std::to_string(tmp.compare(""));
      data.append(tmp);
      tmp =",";
      data.append(tmp);
      tmp = std::to_string(my_items[i].getMyGameObject().getMyLocation().x);
      data.append(tmp);
      tmp =",";
      data.append(tmp);
      tmp = std::to_string(my_items[i].getMyGameObject().getMyLocation().y);
      if (tmp.compare("") >= 0 && tmp.compare("")  < 10)
      {
        tmp ="0";
        data.append(tmp);
        tmp = std::to_string(my_items[i].getMyGameObject().getMyLocation().y);
      }
      tmp = std::to_string(tmp.compare(""));
      data.append(tmp);
      tmp =",";
      data.append(tmp);
      tmp = std::to_string(my_items[i].getMyGameObject().getMyLocation().y);
      data.append(tmp);
      tmp =",";
      data.append(tmp);
    }
  }
  tmp = std::to_string(number_of_exits);
  data.append(tmp);
  tmp =",";
  data.append(tmp);
  for (int i = 0; i < number_of_exits; i++)
  {
    tmp = std::to_string(my_exits[i].isLocked());
    data.append(tmp);
    tmp =",";
    data.append(tmp);
  }
  tmp = std::to_string(my_puzzle.getNumberSwitches());
  data.append(tmp);
  tmp =",";
  data.append(tmp);
  if (my_puzzle.getNumberSwitches() > 0)
  {
    for (int i = 0; i < my_puzzle.getNumberSwitches(); i++)
    {
      tmp = std::to_string(my_puzzle.getMySwitches()[i].isOn());
      data.append(tmp);
      tmp =",";
      data.append(tmp);
    }
  }
  tmp = std::to_string(my_puzzle.getNumberMovables());
  data.append(tmp);
  tmp =",";
  data.append(tmp);
  if (my_puzzle.getNumberMovables() > 0)
  {
    for (int i = 0; i < my_puzzle.getNumberMovables(); i++)
    {
      tmp = std::to_string(my_puzzle.getMyMovables()[i].getMyLocation().x);
      if (tmp.compare("") >= 0 && tmp.compare("")  < 10)
      {
        tmp ="0";
        data.append(tmp);
        tmp = std::to_string(my_puzzle.getMyMovables()[i].getMyLocation().x);
      }
      tmp = std::to_string(tmp.compare(""));
      data.append(tmp);
      tmp =",";
      data.append(tmp);
      tmp = std::to_string(my_puzzle.getMyMovables()[i].getMyLocation().x);
      data.append(tmp);
      tmp =",";
      data.append(tmp);
      tmp = std::to_string(my_puzzle.getMyMovables()[i].getMyLocation().y);
      if (tmp.compare("") >= 0 && tmp.compare("")  < 10)
      {
        tmp ="0";
        data.append(tmp);
        tmp = std::to_string(my_puzzle.getMyMovables()[i].getMyLocation().y);
      }
      tmp = std::to_string(tmp.compare(""));
      data.append(tmp);
      tmp =",";
      data.append(tmp);
      tmp = std::to_string(my_puzzle.getMyMovables()[i].getMyLocation().y);
      data.append(tmp);
      tmp =",";
      data.append(tmp);

      tmp = std::to_string(my_puzzle.getTargetMovableLocations()[i].x);
      if (tmp.compare("") >= 0 && tmp.compare("")  < 10)
      {
        tmp ="0";
        data.append(tmp);
        tmp = std::to_string(my_puzzle.getTargetMovableLocations()[i].x);
      }
      tmp = std::to_string(tmp.compare(""));
      data.append(tmp);
      tmp =",";
      data.append(tmp);
      tmp = std::to_string(my_puzzle.getTargetMovableLocations()[i].x);
      data.append(tmp);
      tmp =",";
      data.append(tmp);
      tmp = std::to_string(my_puzzle.getTargetMovableLocations()[i].y);
      if (tmp.compare("") >= 0 && tmp.compare("")  < 10)
      {
        tmp ="0";
        data.append(tmp);
        tmp = std::to_string(my_puzzle.getTargetMovableLocations()[i].y);
      }
      tmp = std::to_string(tmp.compare(""));
      data.append(tmp);
      tmp =",";
      data.append(tmp);
      tmp = std::to_string(my_puzzle.getTargetMovableLocations()[i].y);
      data.append(tmp);
      tmp =",";
      data.append(tmp);
    }
  }


  using File = ASGE::FILEIO::File;
  File player_data = File();
// open the file in write mode
  if(player_data.open( "/userdata/room" + std::to_string(room_id) + ".dat",
                       ASGE::FILEIO::File::IOMode::WRITE))
  {
    // write the buffer to the file
    player_data.write(data);
  }
  player_data.close();
}

/**
*   @brief   Load room Data
*   @details This function loads the room data
*   @return  void
*/
void Room::loadRoom()
{
  using File = ASGE::FILEIO::File;
  File  file = File();

// attempt to open save data file
  if( file.open( "/userdata/room" + std::to_string(room_id) + ".dat",
                 ASGE::FILEIO::File::IOMode::READ))
  {
    using Buffer = ASGE::FILEIO::IOBuffer;
    size_t length = 0;
    Buffer buffer;
    buffer = file.read();
    size_t string_length = 0;
    Point2D new_position;

    string_length = static_cast<size_t>(std::stoi(buffer.data.get()));
    length +=3;
    file.seek(length);
    buffer = file.read();
    new_position.x = std::stof(buffer.data.get());
    length += string_length + 1;
    file.seek(length);
    buffer = file.read();
    string_length = static_cast<size_t>(std::stoi(buffer.data.get()));
    length +=3;
    file.seek(length);
    buffer = file.read();
    new_position.y = std::stof(buffer.data.get());
    length += string_length + 1;
    file.seek(length);
    buffer = file.read();
    Point2D distance_to_move;
    distance_to_move.x = (new_position.x - my_background[0].getMyLocation().x);
    distance_to_move.y = (new_position.y - my_background[0].getMyLocation().y);
    resetRoomPosition(distance_to_move);
    number_of_items = std::stoi(buffer.data.get());
    length +=3;
    file.seek(length);

    if (number_of_items > 0)
    {
      for (int i = 0; i < number_of_items; i ++)
      {
        buffer = file.read();
        my_items[i].setItemID(std::stoi(buffer.data.get()));
        length +=3;
        file.seek(length);
      }
      for (int i = 0; i < number_of_items; i ++)
      {
        buffer = file.read();
        Point2D tmp;
        my_items[i].setMyGameObject(GameObject(std::stoi(buffer.data.get()), tmp));
        length +=3;
        file.seek(length);
      }
      for (int i = 0; i < number_of_items; i ++)
      {
        Point2D tmp_loc;
        GameObject tmp_gameobject;
        int str_length = 0;
        buffer = file.read();
        str_length = std::stoi(buffer.data.get());
        length +=3;
        file.seek(length);
        buffer = file.read();
        tmp_loc.x = std::stof(buffer.data.get());
        length += str_length + 1;
        file.seek(length);
        buffer = file.read();
        str_length = std::stoi(buffer.data.get());
        length +=3;
        file.seek(length);
        buffer = file.read();
        tmp_loc.y = std::stof(buffer.data.get());
        length += str_length + 1;
        tmp_gameobject = my_items[i].getMyGameObject();
        tmp_gameobject.setMyLocation(tmp_loc);
        my_items[i].setMyGameObject(tmp_gameobject);
        file.seek(length);
      }
    }
    buffer = file.read();
    number_of_exits = std::stoi(buffer.data.get());
    length += 2;
    file.seek(length);
    for (int i = 0; i < number_of_exits; i ++)
    {
      buffer = file.read();
      my_exits[i].setLocked(static_cast<bool>(std::stoi(buffer.data.get())));
      length += 2;
      file.seek(length);
    }
    buffer = file.read();
    my_puzzle.setNumberSwitches(std::stoi(buffer.data.get()));
    length +=2;
    file.seek(length);
    if (my_puzzle.getNumberSwitches() > 0)
    {
      for (int i = 0; i < my_puzzle.getNumberSwitches(); i ++)
      {
        buffer = file.read();
        my_puzzle.getMySwitches()[i].setOn(static_cast<bool>(std::stoi(buffer.data.get())));
        length += 2;
        file.seek(length);
      }
    }
    buffer = file.read();
    my_puzzle.setNumberMovables(std::stoi(buffer.data.get()));
    length +=2;
    file.seek(length);
    if (my_puzzle.getNumberMovables() > 0)
    {
      for (int i = 0; i < my_puzzle.getNumberMovables(); i ++)
      {
        Point2D tmp_loc;
        int str_length = 0;
        buffer = file.read();
        str_length = std::stoi(buffer.data.get());
        length +=3;
        file.seek(length);
        buffer = file.read();
        tmp_loc.x = std::stof(buffer.data.get());
        length += str_length + 1;
        file.seek(length);
        buffer = file.read();
        str_length = std::stoi(buffer.data.get());
        length +=3;
        file.seek(length);
        buffer = file.read();
        tmp_loc.y = std::stof(buffer.data.get());
        length += str_length + 1;
        my_puzzle.getMyMovables()[i].setMyLocation(tmp_loc);
        file.seek(length);
        buffer = file.read();
        str_length = std::stoi(buffer.data.get());
        length +=3;
        file.seek(length);
        buffer = file.read();
        tmp_loc.x = std::stof(buffer.data.get());
        length += str_length + 1;
        file.seek(length);
        buffer = file.read();
        str_length = std::stoi(buffer.data.get());
        length +=3;
        file.seek(length);
        buffer = file.read();
        tmp_loc.y = std::stof(buffer.data.get());
        length += str_length + 1;
        my_puzzle.getTargetMovableLocations()[i].x = tmp_loc.x ;
        my_puzzle.getTargetMovableLocations()[i].y = tmp_loc.y ;
        file.seek(length);
      }
    }
  }
  file.close();
}


void Room::setupFloorStandard()
{
  my_background = new GameObject[(my_gridsize_x*my_gridsize_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                      (GRID_SIZE*
                                       (static_cast<float>(my_gridsize_x)*
                                        0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                     (GRID_SIZE*
                                      (static_cast<float>(my_gridsize_y)*
                                       0.5f)));
  for (int i = 0; i < (my_gridsize_x*my_gridsize_y); i++)
  {
    Point2D new_location;
    new_location.x = left_side;
    new_location.y = top_side;
    my_background[i] = GameObject(0, new_location);
    left_side += GRID_SIZE;
    if (i % my_gridsize_x == my_gridsize_x - 1)
    {
      left_side = static_cast<float>(GAME_WIDTH*0.5-
                                     (GRID_SIZE*
                                      (static_cast<float>(my_gridsize_x)*
                                       0.5f)));
      top_side += GRID_SIZE;
    }
  }
}


void Room::setupWalls()
{
  my_walls = new GameObject[(((my_gridsize_x+my_gridsize_y)*2)+4)];
  auto wall_left_side = static_cast<float>((GAME_WIDTH*0.5)-(
      GRID_SIZE* (static_cast<float>(my_gridsize_x)*
                  0.5f))-GRID_SIZE);
  auto wall_top_side = static_cast<float>((GAME_HEIGHT*0.5)-(
      GRID_SIZE*(static_cast<float>(my_gridsize_y)*
                 0.5f))-GRID_SIZE);

  for (int i = 0; i < (((my_gridsize_x+my_gridsize_y)*2)+4); i++)
  {

    if (i == 0)
    {
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      my_walls[i] = GameObject(TOP_LEFT, new_location);
    }
    else if (i > 0 &&
             i < my_gridsize_x + 1)
    {
      wall_left_side += GRID_SIZE;
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      my_walls[i] = GameObject(TOP, new_location);
    }
    else if (i == my_gridsize_x + 1)
    {
      wall_left_side += GRID_SIZE;
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      my_walls[i] = GameObject(TOP_RIGHT, new_location);
    }
    else if (i > my_gridsize_x + 1 &&
             i < my_gridsize_x + my_gridsize_y + 2)
    {
      wall_left_side = static_cast<float>((GAME_WIDTH ) * 0.5 - (
          GRID_SIZE *(static_cast<float>(my_gridsize_x) * 0.5f))- GRID_SIZE);
      wall_top_side += GRID_SIZE;
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      my_walls[i] = GameObject(LEFT, new_location);
    }

    else if (i == my_gridsize_x + my_gridsize_y + 2)
    {
      wall_top_side = static_cast<float>((GAME_HEIGHT) * 0.5 - (
          GRID_SIZE * (static_cast<float>(my_gridsize_y) * 0.5f)));

      wall_left_side = static_cast<float>((GAME_WIDTH * 0.5) + (
          GRID_SIZE * (static_cast<float>(my_gridsize_x) * 0.5f)));
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      my_walls[i] = GameObject(RIGHT, new_location);
    }
    else if (i > my_gridsize_x + my_gridsize_y + 2 &&
             i < (my_gridsize_x + (my_gridsize_y * 2)) + 2)
    {
      wall_top_side += GRID_SIZE;
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      my_walls[i] = GameObject(RIGHT, new_location);

    }
    else if (i == ((my_gridsize_x + (my_gridsize_y * 2)) + 2))
    {
      wall_left_side = static_cast<float>((GAME_WIDTH ) * 0.5 -(
          GRID_SIZE * (static_cast<float>(my_gridsize_x) *
                       0.5f))- GRID_SIZE);
      wall_top_side += GRID_SIZE;
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      my_walls[i] = GameObject(BOTTOM_LEFT, new_location);
      wall_left_side += GRID_SIZE;
    }

    else if (i > (my_gridsize_x + (my_gridsize_y * 2)) + 2 &&
             i < (my_gridsize_x * 2) + (my_gridsize_y * 2) + 3)
    {
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      my_walls[i] = GameObject(BOTTOM, new_location);
      wall_left_side += GRID_SIZE;
    }
    else if (i ==  (my_gridsize_x * 2) + (my_gridsize_y * 2) + 3)
    {
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      my_walls[i] = GameObject(BOTTOM_RIGHT, new_location);
    }
  }
}