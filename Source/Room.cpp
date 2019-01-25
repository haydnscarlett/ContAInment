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
  number_of_items++;
  my_items = new Item[number_of_items];
  my_items[number_of_items - 1] = new_item;
}

void Room::moveRoom(bool moving, int direction)
{
  if (moving)
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
      ASGE::Sprite* background_sprite = nullptr;
      Point2D new_location = my_background[i].getMyLocation();
      background_sprite = my_background[i].getMySprite();
      switch(direction)
      {
        case SOUTH :
          new_location.y -= GRID_SIZE * 0.25f;
          background_sprite->yPos(new_location.y);
          break;
        case WEST :
          new_location.x += GRID_SIZE* 0.25f;
          background_sprite->xPos(new_location.x);
          break;
        case NORTH :
          new_location.y += GRID_SIZE* 0.25f;
          background_sprite->yPos(new_location.y);
          break;
        case EAST :
          new_location.x -= GRID_SIZE* 0.25f;
          background_sprite->xPos(new_location.x);
          break;
        default :
          break;
      }
      my_background[i].setMySprite(background_sprite);
      my_background[i].setMyLocation(new_location);
    }

    for (int i = 0; i < (((my_gridsize_x + my_gridsize_y) * 2) + 4); i++)
    {
      ASGE::Sprite* wall_sprite = nullptr;
      Point2D new_location = my_walls[i].getMyLocation();
      wall_sprite = my_walls[i].getMySprite();
      switch(direction)
      {
        case SOUTH :
          new_location.y -= GRID_SIZE * 0.25f;
          wall_sprite->yPos(new_location.y);
          break;
        case WEST :
          new_location.x += GRID_SIZE* 0.25f;
          wall_sprite->xPos(new_location.x);
          break;
        case NORTH :
          new_location.y += GRID_SIZE* 0.25f;
          wall_sprite->yPos(new_location.y);
          break;
        case EAST :
          new_location.x -= GRID_SIZE* 0.25f;
          wall_sprite->xPos(new_location.x);
          break;
        default :
          break;
      }
      my_walls[i].setMySprite(wall_sprite);
      my_walls[i].setMyLocation(new_location);
    }

    for (int i = 0; i < (my_gridsize_x * my_gridsize_y); i++)
    {
      if(my_foreground[i].getMySprite() != nullptr)
      {
        ASGE::Sprite* foreground_sprite = nullptr;
        Point2D new_location = my_foreground[i].getMyLocation();
        foreground_sprite = my_foreground[i].getMySprite();
        switch(direction)
        {
          case SOUTH :
            new_location.y -= GRID_SIZE* 0.25f;
            foreground_sprite->yPos(new_location.y);
            break;
          case WEST :
            new_location.x += GRID_SIZE* 0.25f;
            foreground_sprite->xPos(new_location.x);
            break;
          case NORTH :
            new_location.y += GRID_SIZE* 0.25f;
            foreground_sprite->yPos(new_location.y);
            break;
          case EAST :
            new_location.x -= GRID_SIZE* 0.25f;
            foreground_sprite->xPos(new_location.x);
            break;
          default :
            break;
        }
        my_foreground[i].setMySprite(foreground_sprite);
        my_foreground[i].setMyLocation(new_location);

      }
    }
    for (int i = 0; i < number_of_clues; i++)
    {
      clue_gameobjects[i] = my_clues[i].getMyGameObject();
      ASGE::Sprite* clue_sprite = nullptr;
      clue_sprite = clue_gameobjects[i].getMySprite();
      Point2D new_location = clue_gameobjects[i].getMyLocation();
      switch(direction)
      {
        case SOUTH :
          new_location.y -= GRID_SIZE* 0.25f;
          clue_sprite->yPos(new_location.y);
          break;
        case WEST :
          new_location.x += GRID_SIZE* 0.25f;
          clue_sprite->xPos(new_location.x);
          break;
        case NORTH :
          new_location.y += GRID_SIZE* 0.25f;
          clue_sprite->yPos(new_location.y);
          break;
        case EAST :
          new_location.x -= GRID_SIZE* 0.25f;
          clue_sprite->xPos(new_location.x);
          break;
        default :
          break;
      }
      clue_gameobjects[i].setMySprite(clue_sprite);
      clue_gameobjects[i].setMyLocation(new_location);
      my_clues[i].setMyGameObject(clue_gameobjects[i]);
    }
    for (int i = 0; i < number_of_items; i++)
    {
      item_gameobjects[i] = my_items[i].getMyGameObject();
      ASGE::Sprite* item_sprite = nullptr;
      item_sprite = item_gameobjects[i].getMySprite();
      Point2D new_location = item_gameobjects[i].getMyLocation();
      switch(direction)
      {
        case SOUTH :
          new_location.y -= GRID_SIZE* 0.25f;
          item_sprite->yPos(new_location.y);
          break;
        case WEST :
          new_location.x += GRID_SIZE* 0.25f;
          item_sprite->xPos(new_location.x);
          break;
        case NORTH :
          new_location.y += GRID_SIZE* 0.25f;
          item_sprite->yPos(new_location.y);
          break;
        case EAST :
          new_location.x -= GRID_SIZE* 0.25f;
          item_sprite->xPos(new_location.x);
          break;
        default :
          break;
      }
      item_gameobjects[i].setMySprite(item_sprite);
      item_gameobjects[i].setMyLocation(new_location);
      my_items[i].setMyGameObject(item_gameobjects[i]);
    }
    for (int i = 0; i < my_puzzle.getNumberSwitches(); i++)
    {
      switch_on_gameobjects[i] = switches[i].getMyOnGameobject();
      switch_off_gameobjects[i] = switches[i].getMyOffGameobject();
      ASGE::Sprite* switch_on_sprite = nullptr;
      switch_on_sprite = switch_on_gameobjects[i].getMySprite();
      ASGE::Sprite* switch_off_sprite = nullptr;
      switch_off_sprite = switch_off_gameobjects[i].getMySprite();
      Point2D new_location = switch_on_gameobjects[i].getMyLocation();
      switch(direction)
      {
        case SOUTH :
          new_location.y -= GRID_SIZE* 0.25f;
          switch_on_sprite->yPos(new_location.y);
          switch_on_sprite->yPos(new_location.y);
          break;
        case WEST :
          new_location.x += GRID_SIZE* 0.25f;
          switch_on_sprite->xPos(new_location.x);
          switch_off_sprite->xPos(new_location.x);
          break;
        case NORTH :
          new_location.y += GRID_SIZE* 0.25f;
          switch_on_sprite->yPos(new_location.y);
          switch_off_sprite->yPos(new_location.y);
          break;
        case EAST :
          new_location.x -= GRID_SIZE* 0.25f;
          switch_on_sprite->xPos(new_location.x);
          switch_off_sprite->xPos(new_location.x);
          break;
        default :
          break;
      }
      switch_on_gameobjects[i].setMySprite(switch_on_sprite);
      switch_on_gameobjects[i].setMyLocation(new_location);
      switch_off_gameobjects[i].setMySprite(switch_off_sprite);
      switch_off_gameobjects[i].setMyLocation(new_location);
      switches[i].setMyOnGameobject(switch_on_gameobjects[i]);
      switches[i].setMyOffGameobject(switch_off_gameobjects[i]);
    }
    for (int i = 0; i < my_puzzle.getNumberMovables(); i++)
    {
      movable_gameobjects[i] = my_clues[i].getMyGameObject();
      ASGE::Sprite* movable_sprite = nullptr;
      movable_sprite = movable_gameobjects[i].getMySprite();
      Point2D new_location = movable_gameobjects[i].getMyLocation();
      switch(direction)
      {
        case SOUTH :
          new_location.y -= GRID_SIZE* 0.25f;
          movable_sprite->yPos(new_location.y);
          break;
        case WEST :
          new_location.x += GRID_SIZE* 0.25f;
          movable_sprite->xPos(new_location.x);
          break;
        case NORTH :
          new_location.y += GRID_SIZE* 0.25f;
          movable_sprite->yPos(new_location.y);
          break;
        case EAST :
          new_location.x -= GRID_SIZE* 0.25f;
          movable_sprite->xPos(new_location.x);
          break;
        default :
          break;
      }
      movable_gameobjects[i].setMySprite(movable_sprite);
      movable_gameobjects[i].setMyLocation(new_location);
    }
    my_puzzle.setMySwitches(switches);
    my_puzzle.setMyMovables(movable_gameobjects);

    for (int i = 0; i < number_of_exits; i++)
    {
      exit_gameobjects[i] = my_exits[i].getMyExitGameobject();
      ASGE::Sprite* exit_sprite = nullptr;
      Point2D new_location = exit_gameobjects[i].getMyLocation();
      exit_sprite = exit_gameobjects[i].getMySprite();
      switch(direction)
      {
        case SOUTH :
          new_location.y -= GRID_SIZE* 0.25f;
          exit_sprite->yPos(new_location.y);
          break;
        case WEST :
          new_location.x += GRID_SIZE* 0.25f;
          exit_sprite->xPos(new_location.x);
          break;
        case NORTH :
          new_location.y += GRID_SIZE* 0.25f;
          exit_sprite->yPos(new_location.y);
          break;
        case EAST :
          new_location.x -= GRID_SIZE* 0.25f;
          exit_sprite->xPos(new_location.x);
          break;
        default :
          break;
      }
      exit_gameobjects[i].setMySprite(exit_sprite);
      exit_gameobjects[i].setMyLocation(new_location);
      my_exits[i].setMyExitGameobject(exit_gameobjects[i]);
    }
  }
}



bool Room::checkCollisions(Player* player, std::string* text_to_display,
                           int* game_state)
{
  bool colliding = false;

  for (int i = 0; i < (my_gridsize_x * my_gridsize_y); i++)
  {
    if(my_foreground[i].collisionCheck(
        player->getPlayerGameobject().getMyLocation(), player->getDirection()))
    {
      colliding = true;
    }
  }
  for (int i = 0; i < (((my_gridsize_x + my_gridsize_y) * 2) + 4); i++)
  {
    if(my_walls[i].collisionCheck(
        player->getPlayerGameobject().getMyLocation(), player->getDirection()))
    {
      colliding = true;
    }
  }
  for (int i = 0; i < number_of_clues; i++)
  {
    if(my_clues[i].getMyGameObject().collisionCheck(
        player->getPlayerGameobject().getMyLocation(), player->getDirection()))
    {
      colliding = true;
    }
  }
  for (int i = 0; i < number_of_items; i++)
  {
    if(my_items[i].getMyGameObject().collisionCheck(
        player->getPlayerGameobject().getMyLocation(), player->getDirection()))
    {
      colliding = true;
    }
  }

  for (int i = 0; i < number_of_exits; i++)
  {
    if (my_exits[i].isLocked())
    {
      if(my_exits[i].getMyExitGameobject().collisionCheck(
          player->getPlayerGameobject().getMyLocation(), player->getDirection()))
      {
        if(my_puzzle.checkPuzzleCompleted(player))
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
          colliding = true;
        }
      }
    }
  }
  for (int i = 0; i < my_puzzle.getNumberSwitches(); i++)
  {
    if(my_puzzle.getMySwitches()[i].getMyOnGameobject().collisionCheck(
        player->getPlayerGameobject().getMyLocation(), player->getDirection()))
    {
      colliding = true;
    }
  }
  for (int i = 0; i < my_puzzle.getNumberMovables(); i++)
  {
    if(my_puzzle.getMyMovables()[i].collisionCheck(
        player->getPlayerGameobject().getMyLocation(), player->getDirection()))
    {
      colliding = true;
    }
  }
  return colliding;
}

bool Room::checkForInteractables(Player* player, std::string* text_to_display)
{
  bool colliding = false;


  for (int i = 0; i < number_of_clues; i++)
  {
    if(my_clues[i].getMyGameObject().collisionCheck(
        player->getPlayerGameobject().getMyLocation(), player->getDirection()))
    {
      if(my_clues[i].addClueToPlayer(player->getCluesFound(),
                                     player->getNumberCluesFound()))
      {
        player->setNumberCluesFound(player->getNumberCluesFound() + 1);
      }
      *text_to_display = my_clues[i].getItemDescription();
      colliding = true;
    }
  }
  for (int i = 0; i < number_of_items; i++)
  {
    if(my_items[i].getMyGameObject().collisionCheck(
        player->getPlayerGameobject().getMyLocation(), player->getDirection()))
    {
      bool item_added = false;
      for (int j = 0; j < 15; j ++)
      {
        if (player->getInventory(i).getItemID() == -1 && !item_added)
        {
          Item new_item = my_items[i].addItemToInventory();
          *text_to_display = my_items[i].getItemDescription();
          player->addToInventory(new_item, i);
          removeItem(my_items[i].getItemID());
          j = 15;
          item_added = true;
        }

      }
      if (item_added == false)
      {
        *text_to_display = "Inventory full. Please drop something first.";
      }
      colliding = true;
    }
  }
  for (int i = 0; i < my_puzzle.getNumberSwitches(); i++)
  {
    if(my_puzzle.getMySwitches()[i].getMyOnGameobject().collisionCheck(
        player->getPlayerGameobject().getMyLocation(), player->getDirection()))
    {
      my_puzzle.getMySwitches()[i].setOn(!my_puzzle.getMySwitches()[i].isOn());
    }
  }
  return colliding;
}

Room::~Room()
{

}
