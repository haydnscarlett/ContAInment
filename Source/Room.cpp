//
// Created by haydn on 20/01/2019.
//

#include "Room.h"

#include "Constants.h"
GameObject* Room::getMyBackground()
{
  return my_background;
}

void Room::setMyBackground(GameObject* new_background)
{
  my_background = new_background;
}

GameObject* Room::getMyForeground()
{
  return my_foreground;
}

void Room::setMyForeground(GameObject* new_foreground)
{
  my_foreground = new_foreground;
}


GameObject* Room::getMyWalls()
{
  return my_walls;
}

void Room::setMyWalls(GameObject* new_walls)
{
  my_walls = new_walls;
}

Clue* Room::getMyClues()
{
  return my_clues;
}

void Room::setMyClues(Clue* new_clues)
{
  my_clues = new_clues;
}

Item* Room::getMyItems()
{
  return my_items;
}

void Room::setMyItems(Item* new_items)
{
  my_items = new_items;
}

 Puzzle Room::getMyPuzzle()
{
  return my_puzzle;
}

void Room::setMyPuzzle(Puzzle new_puzzle)
{
  my_puzzle = new_puzzle;
}

int Room::getRoomID()
{
  return room_id;
}

void Room::setRoomID(int new_id)
{
  room_id = new_id;
}

Exit* Room::getMyExits()
{
  return my_exits;
}

void Room::setMyExits(Exit* new_exits)
{
  my_exits = new_exits;
}

int Room::getMyGridsizeX()
{
  return my_gridsize_x;
}

void Room::setMyGridsizeX(int new_gridsize_x)
{
  my_gridsize_x = new_gridsize_x;
}

int Room::getMyGridsizeY()
{
  return my_gridsize_y;
}

void Room::setMyGridsizeY(int new_gridsize_y)
{
  my_gridsize_y = new_gridsize_y;
}

int Room::getNumberClues() const
{
  return number_of_clues;
}

void Room::setNumberClues(int new_number_of_clues)
{
  number_of_clues = new_number_of_clues;
}

int Room::getNumberItems() const
{
  return number_of_items;
}

void Room::setNumberItems(int new_number_of_items)
{
  number_of_items = new_number_of_items;
}

int Room::getNumberExits() const
{
  return number_of_exits;
}

void Room::setNumberExits(int new_number_of_exits)
{
  number_of_exits = new_number_of_exits;
}

void Room::removeItem(int item_ID)
{
  Item* temp = new Item[number_of_items];
  for (int i = 0; i < number_of_items; i++)
  {
    if(item_ID != my_items[i].getItemID())
    {
      temp[i] =  my_items[i];
    }
  }
  number_of_items--;
  my_items = new Item[number_of_items];
  for (int i = 0; i < number_of_items; i++)
  {
    my_items[i] = temp[i];
  }
}
void Room::addItem(Item new_item)
{
  Item* tmp = new Item[number_of_items];
  tmp = my_items;
  number_of_items++;
  my_items = new Item[number_of_items];
  for(int i = 0; i < number_of_items - 1; i++)
  {
    my_items[i] = tmp[i];
  }
  my_items[number_of_items - 1] = new_item;
}

void Room::moveRoom(Player* player)
{
  if (player->isMoving())
  {
    Switch* switches = nullptr;
    GameObject* clue_gameobjects = nullptr;
    GameObject* item_gameobjects = nullptr;
    GameObject* switch_on_gameobjects = nullptr;
    GameObject* switch_off_gameobjects = nullptr;
    GameObject* movable_gameobjects = nullptr;
    GameObject* exit_gameobjects = nullptr;

    clue_gameobjects = new GameObject[number_of_clues];
    item_gameobjects = new GameObject[number_of_items];
    switches = my_puzzle.getMySwitches();
    switch_on_gameobjects = new GameObject[my_puzzle.getNumberSwitches()];
    switch_off_gameobjects = new GameObject[my_puzzle.getNumberSwitches()];
    movable_gameobjects = my_puzzle.getMyMovables();
    exit_gameobjects = new GameObject[number_of_exits];


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
      clue_gameobjects[i] = my_clues[i].getMyGameObject();
      Point2D new_location = clue_gameobjects[i].getMyLocation();
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
      clue_gameobjects[i].setMyLocation(new_location);
      my_clues[i].setMyGameObject(clue_gameobjects[i]);
    }
    for (int i = 0; i < number_of_items; i++)
    {
      item_gameobjects[i] = my_items[i].getMyGameObject();
      Point2D new_location = item_gameobjects[i].getMyLocation();
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
      item_gameobjects[i].setMyLocation(new_location);
      my_items[i].setMyGameObject(item_gameobjects[i]);
    }
    for (int i = 0; i < my_puzzle.getNumberSwitches(); i++)
    {
      switch_on_gameobjects[i] = switches[i].getMyOnGameobject();
      switch_off_gameobjects[i] = switches[i].getMyOffGameobject();
      Point2D new_location = switch_on_gameobjects[i].getMyLocation();
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
      switch_on_gameobjects[i].setMyLocation(new_location);
      switch_off_gameobjects[i].setMyLocation(new_location);
      switches[i].setMyOnGameobject(switch_on_gameobjects[i]);
      switches[i].setMyOffGameobject(switch_off_gameobjects[i]);
    }
    my_puzzle.setMySwitches(switches);
    for (int i = 0; i < my_puzzle.getNumberMovables(); i++)
    {
      movable_gameobjects[i] = my_puzzle.getMyMovables()[i];
      if(!movable_gameobjects[i].collisionCheck(
          player->getPlayerGameobject().getMyLocation(),
          player->getDirection(), false))
      {
        Point2D new_location = movable_gameobjects[i].getMyLocation();
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
        movable_gameobjects[i].setMyLocation(new_location);
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
    my_puzzle.setMyMovables(movable_gameobjects);

    for (int i = 0; i < number_of_exits; i++)
    {
      exit_gameobjects[i] = my_exits[i].getMyExitGameobject();
      Point2D new_location = exit_gameobjects[i].getMyLocation();
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
      exit_gameobjects[i].setMyLocation(new_location);
      my_exits[i].setMyExitGameobject(exit_gameobjects[i]);
    }
  }
}

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

bool Room::checkForInteractables(Player* player, std::string* text_to_display,
                                 bool* power_on)
{
  bool colliding = false;


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
      *text_to_display = my_clues[i].getItemDescription();
      colliding = true;
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
              if (player->getCluesFound()[k] == 2)
              {
                Item new_item = my_items[i].addItemToInventory();
                *text_to_display = my_items[i].getItemDescription();
                player->addToInventory(new_item, j);
                removeItem(my_items[i].getItemID());
                j = 15;
                i = number_of_items;
                item_added = true;
                colliding = true;
              }
            }
            if (!item_added)
            {
              *text_to_display = "You do not know the code.";
              colliding = true;
            }

          }
          else
          {
            Item new_item = my_items[i].addItemToInventory();
            *text_to_display = my_items[i].getItemDescription();
            player->addToInventory(new_item, j);
            removeItem(my_items[i].getItemID());
            j = 15;
            item_added = true;
            colliding = true;
          }
        }
        if (j == 14 && !item_added && !colliding)
        {
          *text_to_display = "Inventory full. Please drop something first.";
          colliding = true;
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

    }
  }
   if(my_puzzle.checkPuzzleCompleted(player, power_on) && !*power_on &&
      room_id == REACTOR)
  {
    *power_on = true;
    *text_to_display = my_puzzle.getPuzzleSolvedMessage();
    colliding = true;
  }
  return colliding;
}

Room::~Room()
{

}

void Room::resetRoomPosition(Point2D distance)
{

  Switch* switches = nullptr;
  GameObject* clue_gameobjects = nullptr;
  GameObject* item_gameobjects = nullptr;
  GameObject* switch_on_gameobjects = nullptr;
  GameObject* switch_off_gameobjects = nullptr;
  GameObject* movable_gameobjects = nullptr;
  GameObject* exit_gameobjects = nullptr;

  clue_gameobjects = new GameObject[number_of_clues];
  item_gameobjects = new GameObject[number_of_items];
  switches = my_puzzle.getMySwitches();
  switch_on_gameobjects = new GameObject[my_puzzle.getNumberSwitches()];
  switch_off_gameobjects = new GameObject[my_puzzle.getNumberSwitches()];
  movable_gameobjects = my_puzzle.getMyMovables();
  exit_gameobjects = new GameObject[number_of_exits];


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
    clue_gameobjects[i] = my_clues[i].getMyGameObject();
    Point2D new_location = clue_gameobjects[i].getMyLocation();
    new_location.x += distance.x;
    new_location.y += distance.y;
    clue_gameobjects[i].setMyLocation(new_location);
    my_clues[i].setMyGameObject(clue_gameobjects[i]);
  }
  for (int i = 0; i < number_of_items; i++)
  {
    item_gameobjects[i] = my_items[i].getMyGameObject();
    Point2D new_location = item_gameobjects[i].getMyLocation();
    new_location.x += distance.x;
    new_location.y += distance.y;
    item_gameobjects[i].setMyLocation(new_location);
    my_items[i].setMyGameObject(item_gameobjects[i]);
  }
  for (int i = 0; i < my_puzzle.getNumberSwitches(); i++)
  {
    switch_on_gameobjects[i] = switches[i].getMyOnGameobject();
    switch_off_gameobjects[i] = switches[i].getMyOffGameobject();
    Point2D new_location = switch_on_gameobjects[i].getMyLocation();
    new_location.x += distance.x;
    new_location.y += distance.y;
    switch_on_gameobjects[i].setMyLocation(new_location);
    switch_off_gameobjects[i].setMyLocation(new_location);
    switches[i].setMyOnGameobject(switch_on_gameobjects[i]);
    switches[i].setMyOffGameobject(switch_off_gameobjects[i]);
  }
  my_puzzle.setMySwitches(switches);
  for (int i = 0; i < my_puzzle.getNumberMovables(); i++)
  {
    movable_gameobjects[i] = my_puzzle.getMyMovables()[i];
    Point2D new_location = movable_gameobjects[i].getMyLocation();
    Point2D* new_target_locations = my_puzzle.getTargetMovableLocations();
    new_location.x += distance.x;
    new_location.y += distance.y;
    new_target_locations[i].x += distance.x;
    new_target_locations[i].y += distance.y;
    movable_gameobjects[i].setMyLocation(new_location);
    my_puzzle.setTargetMovableLocations(new_target_locations);
  }
  my_puzzle.setMyMovables(movable_gameobjects);

  for (int i = 0; i < number_of_exits; i++)
  {
    exit_gameobjects[i] = my_exits[i].getMyExitGameobject();
    Point2D new_location = exit_gameobjects[i].getMyLocation();
    new_location.x += distance.x;
    new_location.y += distance.y;
    exit_gameobjects[i].setMyLocation(new_location);
    my_exits[i].setMyExitGameobject(exit_gameobjects[i]);
  }
}


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
  return ;
}



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