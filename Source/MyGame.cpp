//
// Created by Huxy on 03/10/2018.
//

#include <iostream>

#include <Engine/DebugPrinter.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Keys.h>
#include <Engine/Platform.h>
#include <Engine/Sprite.h>

#include "MyGame.h"

/**
*   @brief   Initialises the game
*   @details This function is used to initialise the game.
*   @param   none
*   @return  bool
*/
bool MyGame::init()
{
  game_name = "ContAInment";

  game_height = GAME_HEIGHT;
  game_width = GAME_WIDTH;
  if (!initAPI())
  {
    return false;
  }

  setupGame();

  player_one.setupPlayer();
  setupRoomOne();
  setupRoomTwo();

  current_room = visited_rooms[0];

  inputs->use_threads = false;

  key_callback_id = inputs->addCallbackFnc(
      ASGE::E_KEY, &MyGame::keyHandler, this);
  toggleFPS();



  return true;
}

/**
*   @brief   Setup Game
*   @details This function is used to setup the game.
*   @param   none
*   @return  void
*/
void MyGame::setupGame()
{
  splash_screen = renderer->createRawSprite();
  splash_screen->loadTexture("/data/Splash.png");
  splash_screen->width((GAME_WIDTH * 0.5f));
  splash_screen->height((GAME_HEIGHT * 0.5));
  splash_screen->xPos((GAME_WIDTH * 0.5f) -
                      (splash_screen->width() * 0.5f));
  splash_screen->yPos((GAME_HEIGHT * 0.5f) -
                      (splash_screen->height() * 0.5f));
  main_menu = renderer->createRawSprite();
  main_menu->loadTexture("/data/MainMenu.png");
  main_menu->width(GAME_WIDTH);
  main_menu->height(GAME_HEIGHT);
  main_menu->xPos(0.0f);
  main_menu->yPos(0.0f);


  main_menu_icon = renderer->createRawSprite();
  main_menu_icon->loadTexture("/data/arrow.png");
  main_menu_icon->width(50);
  main_menu_icon->height(50);

  pause_menu = renderer->createRawSprite();
  pause_menu->loadTexture("/data/PauseMenu.png");
  pause_menu->width(GAME_WIDTH);
  pause_menu->height(GAME_HEIGHT);
  pause_menu->xPos(0.0f);
  pause_menu->yPos(0.0f);

  game_screen = renderer->createRawSprite();
  game_screen->loadTexture("/data/GameScreen.png");
  game_screen->width(GAME_WIDTH);
  game_screen->height(GAME_HEIGHT);
  game_screen->xPos(0.0f);
  game_screen->yPos(0.0f);

  text_box = renderer->createRawSprite();
  text_box->loadTexture("/data/TextBox.png");
  text_box->width(GAME_WIDTH);
  text_box->height(GAME_HEIGHT);
  text_box->xPos(0.0f);
  text_box->yPos(0.0f);
  text_to_display = "You awake to discover you are locked in and "
                    "the AI you were testing is missing.\n The power is down!"
                    " You must find a way to escape!";

  inventory_screen = renderer->createRawSprite();
  inventory_screen->loadTexture("/data/Inventory.png");
  inventory_screen->width(GAME_WIDTH);
  inventory_screen->height(GAME_HEIGHT);
  inventory_screen->xPos(0.0f);
  inventory_screen->yPos(0.0f);

  inventory_highlighter = renderer->createRawSprite();
  inventory_highlighter->loadTexture("/data/InventoryHighlight.png");
  inventory_highlighter->width((GRID_SIZE * 2) + 10.0f);
  inventory_highlighter->height((GRID_SIZE * 2) + 10.0f);
  inventory_highlighter->xPos(0.0f);
  inventory_highlighter->yPos(0.0f);


  setupFloorSprites();
  setupWallSprites();
  setupForegroundSprites();
  setupClueSprites();
  setupSwitchSprites();
  setupExitSprites();
  setupItemSprites();
  setupMovableSprites();
  setupPlayerSprites();

  change_room = false;
  power_on = false;
  exit_check[0] = 0;
  exit_check[1] = 0;
  exit_check[2] = 0;
  game_state = SPLASH_SCREEN;
  main_menu_option = NEW_GAME;
}


void MyGame::setupFloorSprites()
{
  for (int i = 0; i < (NUM_FLOOR_SPRITES); i++)
  {
    switch(i)
    {

      case 0 :floor_sprites[i] = renderer->createRawSprite();
        floor_sprites[i]->loadTexture
                            ("/data/Room_Sprites/Floor/floor_1.png");
        break;
      default:break;
    }
  }

}

void MyGame::setupWallSprites()
{
  for (int i = 0; i < (NUM_WALL_SPRITES); i++)
  {
    switch(i)
    {

      case 0 :
        wall_sprites[i] = renderer->createRawSprite();
        wall_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Walls/top_left_wall.png");
        break;
      case 1 :
        wall_sprites[i] = renderer->createRawSprite();
        wall_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Walls/top_wall.png");
        break;
      case 2 :
        wall_sprites[i] = renderer->createRawSprite();
        wall_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Walls/top_right_wall.png");
        break;
      case 3 :
        wall_sprites[i] = renderer->createRawSprite();
        wall_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Walls/left_wall.png");
        break;
      case 4 :
        wall_sprites[i] = renderer->createRawSprite();
        wall_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Walls/right_wall.png");
        break;
      case 5 :
        wall_sprites[i] = renderer->createRawSprite();
        wall_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Walls/bottom_left_wall.png");
        break;
      case 6 :
        wall_sprites[i] = renderer->createRawSprite();
        wall_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Walls/bottom_wall.png");
        break;
      case 7 :
        wall_sprites[i] = renderer->createRawSprite();
        wall_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Walls/bottom_right_wall.png");
        break;
      default:
        break;
    }

  }
}

void MyGame::setupForegroundSprites()
{
  for (int i = 0; i < (NUM_FOREGROUND_SPRITES); i++)
  {
    switch(i)
    {

      case 0 :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/"
                                  "kitchen_counter_left.png");
        break;
      case 1 :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/desk_south.png");
        break;
      case 2 :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/table_top.png");
        break;
      case 3 :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/table_middle.png");
        break;
      case 4 :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/table_bottom.png");
        break;
      default:
        break;
    }

  }
}

void MyGame::setupClueSprites()
{
  for (int i = 0; i < (NUM_CLUE_SPRITES); i++)
  {
    switch(i)
    {

      case 0 :
        clue_sprites[i] = renderer->createRawSprite();
        clue_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Objects/desk_south.png");
        break;
      default:
        break;
    }

  }
}

void MyGame::setupSwitchSprites()
{
  for (int i = 0; i < (NUM_SWITCH_SPRITES); i++)
  {
    switch(i)
    {

      case 0 :
        switch_on_sprites[i] = renderer->createRawSprite();
        switch_on_sprites[i]->loadTexture
                                ("/data/Room_Sprites/Objects/switch_on.png");
        switch_off_sprites[i] = renderer->createRawSprite();
        switch_off_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/switch_off.png");
        break;
      default:
        break;
    }

  }
}

void MyGame::setupExitSprites()
{
  for (int i = 0; i < (NUM_EXIT_SPRITES); i++)
  {
    switch(i)
    {

      case 0 :
        exit_sprites[i] = renderer->createRawSprite();
        exit_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Doors/door_top.png");
        break;
      case 1 :
        exit_sprites[i] = renderer->createRawSprite();
        exit_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Doors/door_right.png");
        break;
      case 2 :
        exit_sprites[i] = renderer->createRawSprite();
        exit_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Doors/door_bottom.png");
        break;
      case 3 :
        exit_sprites[i] = renderer->createRawSprite();
        exit_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Doors/door_left.png");
        break;
      default:
        break;
    }

  }
}

void MyGame::setupItemSprites()
{
  for (int i = 0; i < (NUM_ITEM_SPRITES); i++)
  {
    switch(i)
    {

      case 0 :
        item_sprites[i] = renderer->createRawSprite();
        item_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Objects/Item_Sheet_One/tile024.png");
        break;
      default:
        break;
    }

  }
}

void MyGame::setupMovableSprites()
{
  for (int i = 0; i < (NUM_MOVABLE_SPRITES); i++)
  {
    switch(i)
    {

      case 0 :
        movable_sprites[i] = renderer->createRawSprite();
        movable_sprites[i]->loadTexture
                              ("/data/Room_Sprites/Sci_FI_Sheet_One/tile111.png");
        break;
      default:
        break;
    }

  }
}

void MyGame::setupPlayerSprites()
{
  for (int i = 0; i < 16; i++)
  {
    player_sprites[i] = renderer->createRawSprite();
    std::string texture = "/data/ScientistSprites/tile0";
    switch(i)
    {
      case 0:
        texture.append("00.png");
        break;
      case 1:
        texture.append("01.png");
        break;
      case 2:
        texture.append("02.png");
        break;
      case 3:
        texture.append("03.png");
        break;
      case 4:
        texture.append("04.png");
        break;
      case 5:
        texture.append("05.png");
        break;
      case 6:
        texture.append("06.png");
        break;
      case 7:
        texture.append("07.png");
        break;
      case 8:
        texture.append("08.png");
        break;
      case 9:
        texture.append("09.png");
        break;
      case 10:
        texture.append("10.png");
        break;
      case 11:
        texture.append("11.png");
        break;
      case 12:
        texture.append("12.png");
        break;
      case 13:
        texture.append("13.png");
        break;
      case 14:
        texture.append("14.png");
        break;
      case 15:
        texture.append("15.png");
        break;
    }
    player_sprites[i]->loadTexture(texture);
  }
}


/**
*   @brief   Processes any key inputs
*   @details This function is added as a callback to handle the game's
			 keyboard input. For this game, calls to this function
			 are thread safe, so you may alter the game's state as you
			 see fit.
*   @param   data The event data relating to key input.
*   @see     KeyEvent
*   @return  void
*/
void MyGame::keyHandler(const ASGE::SharedEventData data)
{
  auto key = static_cast<const ASGE::KeyEvent*>(data.get());



  if (key->key == ASGE::KEYS::KEY_ENTER &&
      key->action == ASGE::KEYS::KEY_PRESSED &&
      key->mods == 0x0004)
  {
    if (renderer->getWindowMode() == ASGE::Renderer::WindowMode::WINDOWED)
    {
      renderer->setWindowedMode(ASGE::Renderer::WindowMode::FULLSCREEN);
    }
    else
    {
      renderer->setWindowedMode(ASGE::Renderer::WindowMode::WINDOWED);
    }
  }
  else if(game_state == MAIN_MENU)
  {
    keyHandlerMainMenu(key);
  }
  else if(game_state == IN_GAME)
  {
    keyHandlerInGame(key);
  }
  else if (game_state == TEXT_DISPLAY)
  {
    if((key->key == ASGE::KEYS::KEY_ENTER || key->key == ASGE::KEYS::KEY_SPACE)
       && key->action == ASGE::KEYS::KEY_PRESSED)
    {

      game_state = IN_GAME;
    }
  }
  else if(game_state == INVENTORY)
  {
    keyHandlerInventory(key);
  }
  else if(game_state == PAUSE)
  {
    keyHandlerPauseMenu(key);
  }
  else if(game_state == GAME_OVER)
  {
    if (key->key == ASGE::KEYS::KEY_ESCAPE)
    {
      signalExit();
    }
  }
}

void MyGame::keyHandlerMainMenu(const ASGE::KeyEvent* key)
{
  if (key->key == ASGE::KEYS::KEY_ESCAPE)
  {
    signalExit();
  }
  else if((key->key == ASGE::KEYS::KEY_W || key->key == ASGE::KEYS::KEY_UP)
          && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    main_menu_option--;
    if (main_menu_option < NEW_GAME)
    {
      main_menu_option = EXIT_GAME;
    }
  }
  else if((key->key == ASGE::KEYS::KEY_S || key->key == ASGE::KEYS::KEY_DOWN)
          && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    main_menu_option++;
    if (main_menu_option > EXIT_GAME)
    {
      main_menu_option = NEW_GAME;
    }
  }
  else if(key->key == ASGE::KEYS::KEY_ENTER
          && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    switch(main_menu_option)
    {
      case NEW_GAME:
        game_state = TEXT_DISPLAY;
        break;
      case LOAD_GAME:
        loadGame();
        game_state = IN_GAME;
        break;
      case EXIT_GAME:
        exitGame();
        break;

    }

  }
}

void MyGame::keyHandlerInGame(const ASGE::KeyEvent* key)
{
  if((key->key == ASGE::KEYS::KEY_W || key->key == ASGE::KEYS::KEY_UP)
     && (key->action == ASGE::KEYS::KEY_PRESSED ||
         key->action == ASGE::KEYS::KEY_REPEATED ))
  {
    player_one.setMoving(true);
    player_one.setDirection(NORTH);
  }
  else if((key->key == ASGE::KEYS::KEY_A || key->key == ASGE::KEYS::KEY_LEFT)
          && (key->action == ASGE::KEYS::KEY_PRESSED||
              key->action == ASGE::KEYS::KEY_REPEATED ))
  {
    player_one.setMoving(true);
    player_one.setDirection(WEST);
  }
  else if((key->key == ASGE::KEYS::KEY_S || key->key == ASGE::KEYS::KEY_DOWN)
          && (key->action == ASGE::KEYS::KEY_PRESSED||
              key->action == ASGE::KEYS::KEY_REPEATED ))
  {
    player_one.setMoving(true);
    player_one.setDirection(SOUTH);
  }
  else if((key->key == ASGE::KEYS::KEY_D || key->key == ASGE::KEYS::KEY_RIGHT)
          && (key->action == ASGE::KEYS::KEY_PRESSED||
              key->action == ASGE::KEYS::KEY_REPEATED ))
  {
    player_one.setMoving(true);
    player_one.setDirection(EAST);
  }
  else if(key->key == ASGE::KEYS::KEY_P &&
          key->action == ASGE::KEYS::KEY_PRESSED)
  {
    pause_menu_option = CONTINUE_GAME;
    game_state = PAUSE;
  }
  else if(key->key == ASGE::KEYS::KEY_I &&
          key->action == ASGE::KEYS::KEY_PRESSED)
  {
    inventory_menu_option = 0;
    game_state = INVENTORY;
  }
  else if(key->key == ASGE::KEYS::KEY_SPACE &&
          key->action == ASGE::KEYS::KEY_PRESSED)
  {
    if (current_room.checkForInteractables(&player_one, &text_to_display))
    {
      game_state = TEXT_DISPLAY;
    }
  }
  else
  {
    player_one.setMoving(false);
  }
}

void MyGame::keyHandlerInventory(const ASGE::KeyEvent* key)
{
  if((key->key == ASGE::KEYS::KEY_W || key->key == ASGE::KEYS::KEY_UP)
     && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    inventory_menu_option -= 5;
    if (inventory_menu_option < 0)
    {
      inventory_menu_option += 15;
    }
  }
  else if((key->key == ASGE::KEYS::KEY_S || key->key == ASGE::KEYS::KEY_DOWN)
          && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    inventory_menu_option += 5;
    if (inventory_menu_option > 14)
    {
      inventory_menu_option -= 15;
    }
  }
  else if((key->key == ASGE::KEYS::KEY_A || key->key == ASGE::KEYS::KEY_LEFT)
          && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    inventory_menu_option--;
    if (inventory_menu_option < 0)
    {
      inventory_menu_option = 14;
    }
  }
  else if((key->key == ASGE::KEYS::KEY_D || key->key == ASGE::KEYS::KEY_RIGHT)
          && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    inventory_menu_option++;
    if (inventory_menu_option > 14)
    {
      inventory_menu_option = 0;
    }
  }
  else if(key->key == ASGE::KEYS::KEY_I &&
          key->action == ASGE::KEYS::KEY_PRESSED)
  {
    inventory_menu_option = 0;
    game_state = IN_GAME;
  }
  else if((key->key == ASGE::KEYS::KEY_ENTER || key->key == ASGE::KEYS::KEY_SPACE)
          && key->action == ASGE::KEYS::KEY_PRESSED)
  {

    if(player_one.getInventory(inventory_menu_option).getItemID() != -1)
    {
      Point2D new_location;
      switch(player_one.getDirection())
      {
        case NORTH :
          new_location.x = player_one.getPlayerGameobject().getMyLocation().x;
          new_location.y = player_one.getPlayerGameobject().getMyLocation().y
                           - GRID_SIZE;
          break;
        case EAST :
          new_location.x = player_one.getPlayerGameobject().getMyLocation().x
                           + GRID_SIZE;
          new_location.y = player_one.getPlayerGameobject().getMyLocation().y;
          break;
        case SOUTH :
          new_location.x = player_one.getPlayerGameobject().getMyLocation().x;
          new_location.y = player_one.getPlayerGameobject().getMyLocation().y
                           + GRID_SIZE;
          break;
        case WEST :
          new_location.x = player_one.getPlayerGameobject().getMyLocation().x
                           - GRID_SIZE;
          new_location.y = player_one.getPlayerGameobject().getMyLocation().y;
          break;
        default:
          break;
      }
      game_state = IN_GAME;
      Item new_item = player_one.getInventory(inventory_menu_option);
      GameObject new_gameobject;
      new_gameobject.setMySpriteId(new_item.getMyGameObject().getMySpriteId());
      new_gameobject.setMyLocation(new_location);

      new_item.setMyGameObject(new_gameobject);
      current_room.addItem(new_item);
      new_gameobject.setMySpriteId(-1);
      new_item.setMyGameObject(new_gameobject);
      new_item.setItemID(-1);
      new_item.setItemDescription("");
      new_item.setItemName("");
      player_one.addToInventory(new_item, inventory_menu_option);

    }
  }
}

void MyGame::keyHandlerPauseMenu(const ASGE::KeyEvent* key)
{
  if((key->key == ASGE::KEYS::KEY_W || key->key == ASGE::KEYS::KEY_UP)
     && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    pause_menu_option--;
    if (pause_menu_option < CONTINUE_GAME)
    {
      pause_menu_option = QUIT_GAME;
    }
  }
  else if((key->key == ASGE::KEYS::KEY_S || key->key == ASGE::KEYS::KEY_DOWN)
          && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    pause_menu_option++;
    if (pause_menu_option > QUIT_GAME)
    {
      pause_menu_option = CONTINUE_GAME;
    }
  }
  else if(key->key == ASGE::KEYS::KEY_ENTER
          && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    switch(pause_menu_option)
    {
      case CONTINUE_GAME:
        game_state = IN_GAME;
        break;
      case SAVE_GAME:
        //saveGame();
        break;
      case QUIT_GAME:
        exitGame();
        break;

    }

  }
}

/**
*   @brief   Update
*   @details This function is used to update the game.
*   @param   GameTime
*   @return  void
*/
void MyGame::update(const ASGE::GameTime& game_time)
{
  auto dt_sec = game_time.delta_time.count() / 1000.0f;
  if (game_state == SPLASH_SCREEN)
  {

    splash_screen->width(splash_screen->width() +
                         ((GAME_WIDTH * 0.5f) * 0.3f) *
                         static_cast<float>(dt_sec));
    splash_screen->height(splash_screen->height() +
                          ((GAME_HEIGHT * 0.5f) * 0.3f)	*
                          static_cast<float>(dt_sec));
    splash_screen->xPos((GAME_WIDTH * 0.5f) -
                        (splash_screen->width() * 0.5f));
    splash_screen->yPos((GAME_HEIGHT * 0.5f) -
                        (splash_screen->height() * 0.5f));
    if (splash_screen->xPos() < 0.f)
    {
      game_state = MAIN_MENU;
    }
  }
  else if (game_state == IN_GAME)
  {
    animation_counter += dt_sec;
    current_room.checkExits(&player_one, &text_to_display,
                            &game_state, power_on, exit_check);
    if(current_room.checkCollisions(&player_one, &text_to_display, &game_state))
    {
      player_one.setMoving(false);
    }
    else if(exit_check[0] == 1)
    {
      player_one.setMoving(false);

    }
    else if(exit_check[0] == 2)
    {
      player_one.setMoving(false);

      visited_rooms[current_room.getRoomID()] = current_room;
      current_room = visited_rooms[exit_check[1]];
      Point2D distance;
      switch(current_room.getMyExits()[exit_check[2]].getMyExitGameobject().getMySpriteId())
      {
        case NORTH:
          distance.x = player_one.getPlayerGameobject().getMyLocation().x -
                       current_room.getMyExits()[exit_check[2]]
                           .getMyExitGameobject().getMyLocation().x;
          distance.y = player_one.getPlayerGameobject().getMyLocation().y -
                       current_room.getMyExits()[exit_check[2]]
                           .getMyExitGameobject().getMyLocation().y - GRID_SIZE;
          current_room.resetRoomPosition(distance);
          break;
        case EAST:
          distance.x = player_one.getPlayerGameobject().getMyLocation().x -
                       current_room.getMyExits()[exit_check[2]]
                           .getMyExitGameobject().getMyLocation().x + GRID_SIZE;
          distance.y = player_one.getPlayerGameobject().getMyLocation().y -
                       current_room.getMyExits()[exit_check[2]]
                           .getMyExitGameobject().getMyLocation().y;
          current_room.resetRoomPosition(distance);
          break;
        case SOUTH:
          distance.x = player_one.getPlayerGameobject().getMyLocation().x -
                       current_room.getMyExits()[exit_check[2]]
                           .getMyExitGameobject().getMyLocation().x;
          distance.y = player_one.getPlayerGameobject().getMyLocation().y -
                       current_room.getMyExits()[exit_check[2]]
                           .getMyExitGameobject().getMyLocation().y + GRID_SIZE;
          current_room.resetRoomPosition(distance);
          break;
        case WEST:
          distance.x = player_one.getPlayerGameobject().getMyLocation().x -
                       current_room.getMyExits()[exit_check[2]]
                           .getMyExitGameobject().getMyLocation().x - GRID_SIZE;
          distance.y = player_one.getPlayerGameobject().getMyLocation().y -
                       current_room.getMyExits()[exit_check[2]]
                           .getMyExitGameobject().getMyLocation().y;
          current_room.resetRoomPosition(distance);
          break;
        default:
          break;
      }

    }


    player_one.movePlayer(animation_counter);
    if(animation_counter > 0.08)
    {
      current_room.moveRoom(player_one.isMoving(), player_one.getDirection());

      animation_counter = 0.0;
    }
  }
  return;
}

/**
*   @brief   Render
*   @details This function is used to render the game's sprites and text.
*   @param   GameTime
*   @return  void
*/
void MyGame::render(const ASGE::GameTime& game_time)
{

  switch(game_state)
  {
    case SPLASH_SCREEN:
      renderSplash();
      break;
    case MAIN_MENU:
      renderMainMenu();
      break;
    case IN_GAME:
      renderInGame();
      break;
    case TEXT_DISPLAY:
      renderInGame();
      renderTextDisplay();
      break;
    case PAUSE:
      renderInGame();
      renderPause();
      break;
    case INVENTORY:
      renderInGame();
      renderInventory();
      break;
    case GAME_OVER:
      renderGameOver();
      break;

  }
  return;
}

/**
*   @brief   Render Splash
*   @details This function is used to render the Splash Screen.
*   @param   none
*   @return  void
*/
void MyGame::renderSplash()
{
  renderer->setClearColour(ASGE::COLOURS::BLACK);
  renderer->renderSprite(*splash_screen);
}

/**
*   @brief   Render Main Menu
*   @details This function is used to render the Main Menu.
*   @param   none
*   @return  void
*/
void MyGame::renderMainMenu()
{
  renderer->setClearColour(ASGE::COLOURS::BLACK);
  renderer->renderSprite(*main_menu);
  main_menu_icon->xPos(420.0f);
  switch(main_menu_option)
  {
    case NEW_GAME:
      main_menu_icon->yPos(294.0f);
      break;
    case LOAD_GAME:
      main_menu_icon->yPos(387.0f);
      break;
    case EXIT_GAME:
      main_menu_icon->yPos(480.0f);
      break;
  }

  renderer->renderSprite(*main_menu_icon);
}

/**
*   @brief   Render In Game
*   @details This function is used to render the Game objects.
*   @param   none
*   @return  void
*/
void MyGame::renderInGame()
{
  for (int i = 0; i < (current_room.getMyGridsizeX()*
                       current_room.getMyGridsizeY()); i++)
  {
    floor_sprites[current_room.getMyBackground()[i].getMySpriteId()]
        ->xPos(current_room.getMyBackground()[i].getMyLocation().x);
    floor_sprites[current_room.getMyBackground()[i].getMySpriteId()]
        ->yPos(current_room.getMyBackground()[i].getMyLocation().y);
    floor_sprites[current_room.getMyBackground()[i].getMySpriteId()]
        ->height(GRID_SIZE);
    floor_sprites[current_room.getMyBackground()[i].getMySpriteId()]
        ->width(GRID_SIZE);
    renderer->renderSprite(*floor_sprites[current_room.getMyBackground()[i].getMySpriteId()]);

  }

  for (int i = 0; i < (((current_room.getMyGridsizeX() + current_room.getMyGridsizeY()) * 2) + 4 ); i++)
  {
    wall_sprites[current_room.getMyWalls()[i].getMySpriteId()]
        ->xPos(current_room.getMyWalls()[i].getMyLocation().x);
    wall_sprites[current_room.getMyWalls()[i].getMySpriteId()]
        ->yPos(current_room.getMyWalls()[i].getMyLocation().y);
    wall_sprites[current_room.getMyWalls()[i].getMySpriteId()]
        ->height(GRID_SIZE);
    wall_sprites[current_room.getMyWalls()[i].getMySpriteId()]
        ->width(GRID_SIZE);
    renderer->renderSprite(*wall_sprites[current_room.getMyWalls()[i].getMySpriteId()]);

  }

  player_sprites[player_one.getSpriteIndex()]->xPos(
      player_one.getPlayerGameobject().getMyLocation().x);
  player_sprites[player_one.getSpriteIndex()]->yPos(
      player_one.getPlayerGameobject().getMyLocation().y);
  player_sprites[player_one.getSpriteIndex()]->height(GRID_SIZE);
  player_sprites[player_one.getSpriteIndex()]->width(GRID_SIZE);
  renderer->renderSprite(*player_sprites[player_one.getSpriteIndex()]);


  for (int i = 0; i < (current_room.getMyGridsizeX()*
                       current_room.getMyGridsizeY()); i++)
  {
    if ( current_room.getMyForeground()[i].getMySpriteId() != -1)
    {
      foreground_sprites[
          current_room.getMyForeground()[i].getMySpriteId()]->xPos(
          current_room.getMyForeground()[i].getMyLocation().x);
      foreground_sprites[
          current_room.getMyForeground()[i].getMySpriteId()]->yPos(
          current_room.getMyForeground()[i].getMyLocation().y);
      foreground_sprites[
          current_room.getMyForeground()[i].getMySpriteId()]->height(GRID_SIZE);
      foreground_sprites[
          current_room.getMyForeground()[i].getMySpriteId()]->width(GRID_SIZE);
      renderer->renderSprite(*foreground_sprites[
          current_room.getMyForeground()[i].getMySpriteId()]);
    }

  }


  if (current_room.getMyPuzzle().getNumberSwitches() > 0)
  {
    for(int i = 0; i < current_room.getMyPuzzle().getNumberSwitches(); i++)
    {
      if (current_room.getMyPuzzle().getMySwitches()[i].isOn())
      {
        switch_on_sprites[
            current_room.getMyPuzzle().getMySwitches()[i]
                .getMyOffGameobject().getMySpriteId()]->xPos(
            current_room.getMyPuzzle().getMySwitches()[i]
                .getMyOffGameobject().getMyLocation().x);
        switch_on_sprites[
            current_room.getMyPuzzle().getMySwitches()[i]
                .getMyOffGameobject().getMySpriteId()]->yPos(
            current_room.getMyPuzzle().getMySwitches()[i]
                .getMyOffGameobject().getMyLocation().y);
        switch_on_sprites[
            current_room.getMyPuzzle().getMySwitches()[i]
                .getMyOffGameobject().getMySpriteId()]->height(GRID_SIZE);
        switch_on_sprites[
            current_room.getMyPuzzle().getMySwitches()[i]
                .getMyOffGameobject().getMySpriteId()]->width(GRID_SIZE);
        renderer->renderSprite(*switch_on_sprites[
            current_room.getMyPuzzle().getMySwitches()[i]
                .getMyOffGameobject().getMySpriteId()]);
      }
      else
      {
        switch_off_sprites[
            current_room.getMyPuzzle().getMySwitches()[i]
                .getMyOffGameobject().getMySpriteId()]->xPos(
            current_room.getMyPuzzle().getMySwitches()[i]
                .getMyOffGameobject().getMyLocation().x);
        switch_off_sprites[
            current_room.getMyPuzzle().getMySwitches()[i]
                .getMyOffGameobject().getMySpriteId()]->yPos(
            current_room.getMyPuzzle().getMySwitches()[i]
                .getMyOffGameobject().getMyLocation().y);
        switch_off_sprites[
            current_room.getMyPuzzle().getMySwitches()[i]
                .getMyOffGameobject().getMySpriteId()]->height(GRID_SIZE);
        switch_off_sprites[
            current_room.getMyPuzzle().getMySwitches()[i]
                .getMyOffGameobject().getMySpriteId()]->width(GRID_SIZE);
        renderer->renderSprite(*switch_off_sprites[
            current_room.getMyPuzzle().getMySwitches()[i]
                .getMyOffGameobject().getMySpriteId()]);
      }

    }
  }

  for(int i = 0; i < current_room.getMyPuzzle().getNumberMovables(); i++)
  {
    movable_sprites[
        current_room.getMyPuzzle().getMyMovables()[i].getMySpriteId()]->xPos(
        current_room.getMyPuzzle().getMyMovables()[i].getMyLocation().x);
    movable_sprites[
        current_room.getMyPuzzle().getMyMovables()[i].getMySpriteId()]->yPos(
        current_room.getMyPuzzle().getMyMovables()[i].getMyLocation().y);
    movable_sprites[
        current_room.getMyPuzzle().getMyMovables()[i].getMySpriteId()]
        ->height(GRID_SIZE);
    movable_sprites[
        current_room.getMyPuzzle().getMyMovables()[i].getMySpriteId()]
        ->width(GRID_SIZE);
    renderer->renderSprite(*movable_sprites[
        current_room.getMyPuzzle().getMyMovables()[i].getMySpriteId()]);
  }



  for(int i = 0; i < current_room.getNumberItems(); i++)
  {
    item_sprites[
        current_room.getMyItems()[i].getMyGameObject().getMySpriteId()]->xPos(
        current_room.getMyItems()[i].getMyGameObject().getMyLocation().x);
    item_sprites[
        current_room.getMyItems()[i].getMyGameObject().getMySpriteId()]->yPos(
        current_room.getMyItems()[i].getMyGameObject().getMyLocation().y);
    item_sprites[
        current_room.getMyItems()[i].getMyGameObject().getMySpriteId()]
        ->height(GRID_SIZE);
    item_sprites[
        current_room.getMyItems()[i].getMyGameObject().getMySpriteId()]
        ->width(GRID_SIZE);
    renderer->renderSprite(*item_sprites[
        current_room.getMyItems()[i].getMyGameObject().getMySpriteId()]);
  }
  for(int i = 0; i < current_room.getNumberClues(); i++)
  {
    clue_sprites[
        current_room.getMyClues()[i].getMyGameObject().getMySpriteId()]->xPos(
        current_room.getMyClues()[i].getMyGameObject().getMyLocation().x);
    clue_sprites[
        current_room.getMyClues()[i].getMyGameObject().getMySpriteId()]->yPos(
        current_room.getMyClues()[i].getMyGameObject().getMyLocation().y);
    clue_sprites[
        current_room.getMyClues()[i].getMyGameObject().getMySpriteId()]
        ->height(GRID_SIZE);
    clue_sprites[
        current_room.getMyClues()[i].getMyGameObject().getMySpriteId()]
        ->width(GRID_SIZE);
    renderer->renderSprite(*clue_sprites[
        current_room.getMyClues()[i].getMyGameObject().getMySpriteId()]);
  }

  for(int i = 0; i < current_room.getNumberExits(); i++)
  {
    exit_sprites[
        current_room.getMyExits()[i].getMyExitGameobject().getMySpriteId()]->xPos(
        current_room.getMyExits()[i].getMyExitGameobject().getMyLocation().x);
    exit_sprites[
        current_room.getMyExits()[i].getMyExitGameobject().getMySpriteId()]->yPos(
        current_room.getMyExits()[i].getMyExitGameobject().getMyLocation().y);
    exit_sprites[
        current_room.getMyExits()[i].getMyExitGameobject().getMySpriteId()]
        ->height(GRID_SIZE);
    exit_sprites[
        current_room.getMyExits()[i].getMyExitGameobject().getMySpriteId()]
        ->width(GRID_SIZE);
    renderer->renderSprite(*exit_sprites[
        current_room.getMyExits()[i].getMyExitGameobject().getMySpriteId()]);
  }
  renderer->renderSprite(*game_screen);
}

/**
*   @brief   Render Text Display
*   @details This function is used to render text to the player.
*   @param   none
*   @return  void
*/
void MyGame::renderTextDisplay()
{

  renderer->renderSprite(*text_box);

  // renders the main menu text
  renderer->renderText(text_to_display, 250,
                       465, 1, ASGE::COLOURS::WHITESMOKE);

}

/**
*   @brief   Render Pause
*   @details This function is used to render the Pause Menu.
*   @param   none
*   @return  void
*/
void MyGame::renderPause()
{
  renderer->renderSprite(*pause_menu);
  main_menu_icon->xPos(390.0f);
  switch(pause_menu_option)
  {
    case CONTINUE_GAME:
      main_menu_icon->yPos(265.0f);
      break;
    case SAVE_GAME:
      main_menu_icon->yPos(356.0f);
      break;
    case QUIT_GAME:
      main_menu_icon->yPos(447.0f);
      break;
  }

  renderer->renderSprite(*main_menu_icon);
}

/**
*   @brief   Render GameOver
*   @details This function is used to render the ending Screen.
*   @param   none
*   @return  void
*/
void MyGame::renderGameOver()
{

}

/**
*   @brief   Render Inventory
*   @details This function is used to render the Inventory Screen.
*   @param   none
*   @return  void
*/
void MyGame::renderInventory()
{


  renderer->renderSprite(*inventory_screen);
  float new_x = 250.0f;
  float new_y = 93.0f;

  for(int i = 0; i < 15; i++)
  {
    if(player_one.getInventory(i).getItemID() != -1)
    {
      item_sprites[player_one.getInventory(i).getMyGameObject()
                             .getMySpriteId()]->xPos(new_x);
      item_sprites[player_one.getInventory(i).getMyGameObject()
                             .getMySpriteId()]->yPos(new_y);

      item_sprites[player_one.getInventory(i).getMyGameObject()
                             .getMySpriteId()]->height( GRID_SIZE * 2);

      item_sprites[player_one.getInventory(i).getMyGameObject()
                             .getMySpriteId()]->width( GRID_SIZE * 2);
      renderer->renderSprite(*item_sprites[
          player_one.getInventory(i).getMyGameObject().getMySpriteId()]);

    }
    new_x += 190.0f;
    if(i == 4)
    {
      new_x = 250.0f;
      new_y = 277.0f;
    }
    if(i == 9)
    {
      new_x = 250.0f;
      new_y = 465.0f;
    }
  }




  switch(inventory_menu_option)
  {
    case 0:
      inventory_highlighter->xPos(250.0f);
      inventory_highlighter->yPos(93.0f);
      if(player_one.getInventory(0).getItemID() != -1)
      {
        renderer->renderText("Drop the " +
                             (player_one.getInventory(0).getItemName() + "?"),
                             260, 700, 1, ASGE::COLOURS::WHITESMOKE);

      }
      break;
    case 1:
      inventory_highlighter->xPos(440.0f);
      inventory_highlighter->yPos(93.0f);
      if(player_one.getInventory(1).getItemID() != -1)
      {
        renderer->renderText("Drop the " +
                             (player_one.getInventory(0).getItemName() + "?"),
                             260, 700, 1, ASGE::COLOURS::WHITESMOKE);

      }
      break;
    case 2:
      inventory_highlighter->xPos(630.0f);
      inventory_highlighter->yPos(93.0f);
      if(player_one.getInventory(2).getItemID() != -1)
      {
        renderer->renderText("Drop the " +
                             (player_one.getInventory(0).getItemName() + "?"),
                             260, 700, 1, ASGE::COLOURS::WHITESMOKE);

      }
      break;
    case 3:
      inventory_highlighter->xPos(820.0f);
      inventory_highlighter->yPos(93.0f);
      if(player_one.getInventory(3).getItemID() != -1)
      {
        renderer->renderText("Drop the " +
                             (player_one.getInventory(0).getItemName() + "?"),
                             260, 700, 1, ASGE::COLOURS::WHITESMOKE);

      }
      break;
    case 4:
      inventory_highlighter->xPos(1010.0f);
      inventory_highlighter->yPos(93.0f);
      if(player_one.getInventory(4).getItemID() != -1)
      {
        renderer->renderText("Drop the " +
                             (player_one.getInventory(0).getItemName() + "?"),
                             260, 700, 1, ASGE::COLOURS::WHITESMOKE);

      }
      break;
    case 5:
      inventory_highlighter->xPos(250.0f);
      inventory_highlighter->yPos(277.0f);
      if(player_one.getInventory(5).getItemID() != -1)
      {
        renderer->renderText("Drop the " +
                             (player_one.getInventory(0).getItemName() + "?"),
                             260, 700, 1, ASGE::COLOURS::WHITESMOKE);

      }
      break;
    case 6:
      inventory_highlighter->xPos(440.0f);
      inventory_highlighter->yPos(277.0f);
      if(player_one.getInventory(6).getItemID() != -1)
      {
        renderer->renderText("Drop the " +
                             (player_one.getInventory(0).getItemName() + "?"),
                             260, 700, 1, ASGE::COLOURS::WHITESMOKE);

      }
      break;
    case 7:
      inventory_highlighter->xPos(630.0f);
      inventory_highlighter->yPos(277.0f);
      if(player_one.getInventory(7).getItemID() != -1)
      {
        renderer->renderText("Drop the " +
                             (player_one.getInventory(0).getItemName() + "?"),
                             260, 700, 1, ASGE::COLOURS::WHITESMOKE);

      }
      break;
    case 8:
      inventory_highlighter->xPos(820.0f);
      inventory_highlighter->yPos(277.0f);
      if(player_one.getInventory(8).getItemID() != -1)
      {
        renderer->renderText("Drop the " +
                             (player_one.getInventory(0).getItemName() + "?"),
                             260, 700, 1, ASGE::COLOURS::WHITESMOKE);

      }
      break;
    case 9:
      inventory_highlighter->xPos(1010.0f);
      inventory_highlighter->yPos(277.0f);
      if(player_one.getInventory(9).getItemID() != -1)
      {
        renderer->renderText("Drop the " +
                             (player_one.getInventory(0).getItemName() + "?"),
                             260, 700, 1, ASGE::COLOURS::WHITESMOKE);

      }
      break;
    case 10:
      inventory_highlighter->xPos(250.0f);
      inventory_highlighter->yPos(465.0f);
      if(player_one.getInventory(10).getItemID() != -1)
      {
        renderer->renderText("Drop the " +
                             (player_one.getInventory(0).getItemName() + "?"),
                             260, 700, 1, ASGE::COLOURS::WHITESMOKE);

      }
      break;
    case 11:
      inventory_highlighter->xPos(440.0f);
      inventory_highlighter->yPos(465.0f);
      if(player_one.getInventory(11).getItemID() != -1)
      {
        renderer->renderText("Drop the " +
                             (player_one.getInventory(0).getItemName() + "?"),
                             260, 700, 1, ASGE::COLOURS::WHITESMOKE);

      }
      break;
    case 12:
      inventory_highlighter->xPos(630.0f);
      inventory_highlighter->yPos(465.0f);
      if(player_one.getInventory(12).getItemID() != -1)
      {
        renderer->renderText("Drop the " +
                             (player_one.getInventory(0).getItemName() + "?"),
                             260, 700, 1, ASGE::COLOURS::WHITESMOKE);

      }
      break;
    case 13:
      inventory_highlighter->xPos(820.0f);
      inventory_highlighter->yPos(465.0f);
      if(player_one.getInventory(13).getItemID() != -1)
      {
        renderer->renderText("Drop the " +
                             (player_one.getInventory(0).getItemName() + "?"),
                             260, 700, 1, ASGE::COLOURS::WHITESMOKE);

      }
      break;
    case 14:
      inventory_highlighter->xPos(1010.0f);
      inventory_highlighter->yPos(465.0f);
      if(player_one.getInventory(14).getItemID() != -1)
      {
        renderer->renderText("Drop the " +
                             (player_one.getInventory(0).getItemName() + "?"),
                             260, 700, 1, ASGE::COLOURS::WHITESMOKE);

      }
      break;
    default:
      break;

  }


  renderer->renderSprite(*inventory_highlighter);

}

/**
*   @brief   Exit Game
*   @details This function is used to exit the game.
*   @param   none
*   @return  void
*/
void MyGame::exitGame()
{
  player_one.savePlayerData();
  signalExit();
}

/**
*   @brief   Load Game
*   @details This function is used to load the game data.
*   @param   none
*   @return  void
*/
void MyGame::loadGame()
{
  player_one.loadPlayerData();
}

/**
*   @brief   Setup Rooms
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomOne()
{
  Room new_room;
  GameObject* new_background = nullptr;
  GameObject* new_foreground = nullptr;
  GameObject* new_walls = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle;
  Exit* new_exits = nullptr;
  int new_grid_size_x = 15;
  int new_grid_size_y = 7;

  new_room.setRoomID(0);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_background = new GameObject[(new_grid_size_x*new_grid_size_y)];
  float left_side = static_cast<float>(GAME_WIDTH*0.5-
                                       (GRID_SIZE*
                                        (static_cast<float>(new_grid_size_x)*
                                         0.5f)));
  float top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                      (GRID_SIZE*
                                       (static_cast<float>(new_grid_size_y)*
                                        0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {
    Point2D new_location;
    new_location.x = left_side;
    new_location.y = top_side;
    new_background[i] = GameObject(0, new_location);
    left_side += GRID_SIZE;
    if (i%new_grid_size_x == new_grid_size_x-1)
    {
      left_side = static_cast<float>(GAME_WIDTH*0.5-
                                     (GRID_SIZE*
                                      (static_cast<float>(new_grid_size_x)*
                                       0.5f)));
      top_side += GRID_SIZE;
    }
  }
  new_room.setMyBackground(new_background);

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  left_side = static_cast<float>(GAME_WIDTH*0.5-
                                 (GRID_SIZE*
                                  (static_cast<float>(new_grid_size_x)*0.5f)));
  top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                (GRID_SIZE*
                                 (static_cast<float>(new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {
    if (i == 8)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(0, new_location);
    }
    else if (i == 9)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(1, new_location);
    }
    else if (i == 30)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(2, new_location);
    }
    else if (i == 45)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(3, new_location);
    }
    else if (i == 60)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(3, new_location);
    }
    else if (i == 75)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(4, new_location);
    }
    else
    {
      new_foreground[i].setMySpriteId(-1);
    }
    left_side += GRID_SIZE;
    if (i%new_grid_size_x == new_grid_size_x-1)
    {
      left_side = static_cast<float>(GAME_WIDTH*0.5-
                                     (GRID_SIZE*
                                      (static_cast<float>(new_grid_size_x)*
                                       0.5f)));
      top_side += GRID_SIZE;
    }

  }
  new_room.setMyForeground(new_foreground);

  new_walls = new GameObject[(((new_grid_size_x+new_grid_size_y)*2)+4)];
  float wall_left_side = static_cast<float>((GAME_WIDTH*0.5)-
                                            (GRID_SIZE*
                                             (static_cast<float>(new_grid_size_x)*
                                              0.5f))-GRID_SIZE);
  float wall_top_side = static_cast<float>((GAME_HEIGHT*0.5)-
                                           (GRID_SIZE*
                                            (static_cast<float>(new_grid_size_y)*
                                             0.5f))-GRID_SIZE);

  for (int i = 0; i < (((new_grid_size_x+new_grid_size_y)*2)+4); i++)
  {
    if (i == 0)
    {
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      new_walls[i] = GameObject(0, new_location);
    }
    else if (i > 0 &&
             i < new_grid_size_x+1)
    {
      wall_left_side += GRID_SIZE;
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      new_walls[i] = GameObject(1, new_location);
    }
    else if (i == new_grid_size_x + 1)
    {

      wall_left_side += GRID_SIZE;
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      new_walls[i] = GameObject(2, new_location);
    }
    else if (i > new_grid_size_x+1 &&
             i < new_grid_size_x+new_grid_size_y+2)
    {
      wall_left_side = static_cast<float>((GAME_WIDTH)*0.5-(GRID_SIZE*
                                                            (static_cast<float>(new_grid_size_x)*
                                                             0.5f))-GRID_SIZE);
      wall_top_side += GRID_SIZE;
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      new_walls[i] = GameObject(3, new_location);
    }

    else if (i == new_grid_size_x+new_grid_size_y+2)
    {
      wall_top_side = static_cast<float>((GAME_HEIGHT)*0.5-
                                         (GRID_SIZE*
                                          (static_cast<float>(new_grid_size_y)*
                                           0.5f)));

      wall_left_side = static_cast<float>((GAME_WIDTH*0.5)+(GRID_SIZE*
                                                            (static_cast<float>(new_grid_size_x)*
                                                             0.5f)));
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      new_walls[i] = GameObject(4, new_location);
    }
    else if (i > new_grid_size_x+new_grid_size_y+2 &&
             i < (new_grid_size_x*2)+1)
    {
      wall_top_side += GRID_SIZE;
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      new_walls[i] = GameObject(4, new_location);

    }
    else if (i == (new_grid_size_x*2)+1)
    {
      wall_left_side = static_cast<float>((GAME_WIDTH)*0.5-
                                          (GRID_SIZE*
                                           (static_cast<float>(new_grid_size_x)*
                                            0.5f))-GRID_SIZE);
      wall_top_side += GRID_SIZE;
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      new_walls[i] = GameObject(5, new_location);
      wall_left_side += GRID_SIZE;
    }

    else if (i > (new_grid_size_x*2)+1 &&
             i < (new_grid_size_x*2)+(new_grid_size_y*2)+3)
    {
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      new_walls[i] = GameObject(6, new_location);
      wall_left_side += GRID_SIZE;
    }
    else if (i == (new_grid_size_x*2)+(new_grid_size_y*2)+3)
    {
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      new_walls[i] = GameObject(7, new_location);
    }
  }
  new_room.setMyWalls(new_walls);

  new_room.setNumberClues(1);
  new_clues = new Clue[new_room.getNumberClues()];
  for (int i = 0; i < new_room.getNumberClues(); i++)
  {
    if (i == 0)
    {
      GameObject new_gameobject = new_foreground[9];
      new_gameobject.setMySpriteId(0);
      new_clues[i] = Clue(new_gameobject, 1, "There is no power.");
    }
  }
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(1);
  new_items = new Item[new_room.getNumberItems()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      GameObject new_gameobject = new_background[60];
      Point2D new_location;
      new_location = new_gameobject.getMyLocation();
      new_items[i] = Item(GameObject(0, new_location), 0,
                          "You found a screwdriver", "Screwdriver");

    }

  }
  new_room.setMyItems(new_items);

  new_puzzle.setNumberLinkedExits(1);
  int* new_linked_exits = nullptr;
  new_linked_exits = new int[new_puzzle.getNumberLinkedExits()];
  for (int i = 0; i < new_puzzle.getNumberLinkedExits(); i++)
  {
    if (i == 0)
    {
      new_linked_exits[0] = 0;
    }
  }
  new_puzzle.setLinkedExits(new_linked_exits);

  Switch* new_switches = nullptr;
  bool* new_target_switch_states = nullptr;
  new_puzzle.setNumberSwitches(0);
  new_switches = new Switch[new_puzzle.getNumberSwitches()];
  new_target_switch_states = new bool[new_puzzle.getNumberSwitches()];
  for (int i = 0; i < new_puzzle.getNumberSwitches(); i++)
  {
    if (i == 0)
    {
      Point2D new_location;
      new_switches[i] = Switch(GameObject(0, new_location),
                               GameObject(0, new_location),
                               false);
      new_target_switch_states[i] = true;
    }
  }
  new_puzzle.setMySwitches(new_switches);
  new_puzzle.setTargetSwitchStates(new_target_switch_states);

  GameObject* new_movable_gameobjects = nullptr;
  new_puzzle.setNumberMovables(0);
  new_movable_gameobjects = new GameObject[new_puzzle.getNumberMovables()];
  Point2D* new_target_movable_locations = nullptr;
  new_target_movable_locations = new Point2D[new_puzzle.getNumberMovables()];
  for (int i = 0; i < new_puzzle.getNumberSwitches(); i++)
  {
    if (i == 0)
    {
      Point2D new_location;
      Point2D new_target_location;
      new_movable_gameobjects[i] = GameObject(0, new_location);
      new_target_movable_locations[i] = new_target_location;
    }
  }
  new_puzzle.setMyMovables(new_movable_gameobjects);
  new_puzzle.setTargetMovableLocations(new_target_movable_locations);

  std::string new_puzzle_solved_message = "You use the screwdriver to "
                                          "unlock the door.";
  new_puzzle.setPuzzleSolvedMessage(new_puzzle_solved_message);

  new_puzzle.setPuzzleID(0);
  new_puzzle.setRequiredItemID(0);
  new_puzzle.setPowerRequired(false);

  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(1);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_background[74].getMyLocation();
      new_exits[i] = Exit(GameObject(1, new_exit_location), 0, 1, 2, true);
    }

  }
  new_room.setMyExits(new_exits);
  visited_rooms[0] = new_room;
}

/**
*   @brief   Setup Rooms
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomTwo()
{

  Room new_room;
  GameObject* new_background = nullptr;
  GameObject* new_foreground = nullptr;
  GameObject* new_walls = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle;
  Exit* new_exits = nullptr;
  int new_grid_size_x = 20;
  int new_grid_size_y = 8;

  new_room.setRoomID(1);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_background = new GameObject[(new_grid_size_x * new_grid_size_y)];
  float left_side = static_cast<float>(GAME_WIDTH * 0.5 -
      (GRID_SIZE * (static_cast<float>(new_grid_size_x) * 0.5f)));
  float top_side = static_cast<float>(GAME_HEIGHT * 0.5 -
      (GRID_SIZE * (static_cast<float>(new_grid_size_y) * 0.5f)));
  for (int i = 0; i < (new_grid_size_x * new_grid_size_y); i++)
  {
    Point2D new_location;
    new_location.x = left_side;
    new_location.y = top_side;
    new_background[i] = GameObject(0, new_location);
    left_side += GRID_SIZE;
    if (i % new_grid_size_x == new_grid_size_x - 1)
    {
      left_side = static_cast<float>(GAME_WIDTH * 0.5 -
          (GRID_SIZE * (static_cast<float>(new_grid_size_x) * 0.5f)));
      top_side += GRID_SIZE;
    }
  }
  new_room.setMyBackground(new_background);

  new_foreground = new GameObject[(new_grid_size_x * new_grid_size_y)];
  left_side = static_cast<float>(GAME_WIDTH * 0.5 -
      (GRID_SIZE * (static_cast<float>(new_grid_size_x) * 0.5f)));
  top_side = static_cast<float>(GAME_HEIGHT * 0.5 -
      (GRID_SIZE * (static_cast<float>(new_grid_size_y) * 0.5f)));
  for (int i = 0; i < (new_grid_size_x * new_grid_size_y); i++)
  {


    new_foreground[i].setMySpriteId(-1);

    left_side += GRID_SIZE;
    if (i % new_grid_size_x == new_grid_size_x - 1)
    {
      left_side = static_cast<float>(GAME_WIDTH * 0.5 -
          (GRID_SIZE * (static_cast<float>(new_grid_size_x) * 0.5f)));
      top_side += GRID_SIZE;
    }

  }
  new_room.setMyForeground(new_foreground);


  new_walls = new GameObject[(((new_grid_size_x + new_grid_size_y) * 2) + 4)];
  float wall_left_side = static_cast<float>((GAME_WIDTH  * 0.5) -
      (GRID_SIZE * (static_cast<float>(new_grid_size_x) * 0.5f))- GRID_SIZE);
  float wall_top_side = static_cast<float>((GAME_HEIGHT * 0.5) -
      (GRID_SIZE * (static_cast<float>(new_grid_size_y) * 0.5f)) - GRID_SIZE);

  for (int i = 0; i < (((new_grid_size_x + new_grid_size_y) * 2) + 4); i++)
  {
    if (i == 0)
    {
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      new_walls[i] = GameObject(0, new_location);
    }
    else if (i > 0 &&
             i < new_grid_size_x + 1)
    {
      wall_left_side += GRID_SIZE;
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      new_walls[i] = GameObject(1, new_location);
    }
    else if (i == new_grid_size_x + 1)
    {


      wall_left_side += GRID_SIZE;
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      new_walls[i] = GameObject(2, new_location);
    }
    else if (i > new_grid_size_x + 1 &&
             i < new_grid_size_x + new_grid_size_y + 2)
    {
      wall_left_side = static_cast<float>((GAME_WIDTH ) * 0.5 - (
          GRID_SIZE *(static_cast<float>(new_grid_size_x) * 0.5f))- GRID_SIZE);
      wall_top_side += GRID_SIZE;
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      new_walls[i] = GameObject(3, new_location);
    }

    else if (i == new_grid_size_x + new_grid_size_y + 2)
    {
      wall_top_side = static_cast<float>((GAME_HEIGHT) * 0.5 -
          (GRID_SIZE * (static_cast<float>(new_grid_size_y) * 0.5f)));

      wall_left_side = static_cast<float>((GAME_WIDTH * 0.5) + (GRID_SIZE *
          (static_cast<float>(new_grid_size_x) * 0.5f)) );
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      new_walls[i] = GameObject(4, new_location);
    }
    else if (i > new_grid_size_x + new_grid_size_y + 2 &&
             i < (new_grid_size_x + (new_grid_size_y * 2)) + 2)
    {
      wall_top_side += GRID_SIZE;
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      new_walls[i] = GameObject(4, new_location);

    }
    else if (i == ((new_grid_size_x + (new_grid_size_y * 2)) + 2))
    {
      wall_left_side = static_cast<float>((GAME_WIDTH ) * 0.5 -
          (GRID_SIZE * (static_cast<float>(new_grid_size_x) * 0.5f))- GRID_SIZE);
      wall_top_side += GRID_SIZE;
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      new_walls[i] = GameObject(5, new_location);
      wall_left_side += GRID_SIZE;
    }

    else if (i > (new_grid_size_x + (new_grid_size_y * 2)) + 2 &&
             i < (new_grid_size_x * 2) + (new_grid_size_y * 2) + 3)
    {
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      new_walls[i] = GameObject(6, new_location);
      wall_left_side += GRID_SIZE;
    }
    else if (i ==  (new_grid_size_x * 2) + (new_grid_size_y * 2) + 3)
    {
      Point2D new_location;
      new_location.x = wall_left_side;
      new_location.y = wall_top_side;
      new_walls[i] = GameObject(7, new_location);
    }
  }
  new_room.setMyWalls(new_walls);

  new_room.setNumberClues(0);
  new_clues = new Clue[new_room.getNumberClues()];
  for (int i = 0; i < new_room.getNumberClues(); i++)
  {

  }
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(0);
  new_items = new Item[new_room.getNumberItems()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {

  }
  new_room.setMyItems(new_items);

  new_puzzle.setNumberLinkedExits(1);
  int* new_linked_exits = nullptr;
  new_linked_exits = new int[new_puzzle.getNumberLinkedExits()];
  for (int i = 0; i < new_puzzle.getNumberLinkedExits(); i++)
  {
    if (i == 0)
    {
      new_linked_exits[0] = 0;
    }
  }
  new_puzzle.setLinkedExits(new_linked_exits);

  Switch* new_switches = nullptr;
  bool* new_target_switch_states = nullptr;
  new_puzzle.setNumberSwitches(0);
  new_switches = new Switch[new_puzzle.getNumberSwitches()];
  new_target_switch_states = new bool[new_puzzle.getNumberSwitches()];
  for (int i = 0; i < new_puzzle.getNumberSwitches(); i++)
  {

  }
  new_puzzle.setMySwitches(new_switches);
  new_puzzle.setTargetSwitchStates(new_target_switch_states);


  GameObject* new_movable_gameobjects = nullptr;
  new_puzzle.setNumberMovables(0);
  new_movable_gameobjects = new GameObject[new_puzzle.getNumberMovables()];
  Point2D* new_target_movable_locations = nullptr;
  new_target_movable_locations = new Point2D[new_puzzle.getNumberMovables()];
  for (int i = 0; i < new_puzzle.getNumberSwitches(); i++)
  {

  }
  new_puzzle.setMyMovables(new_movable_gameobjects);
  new_puzzle.setTargetMovableLocations(new_target_movable_locations);

  std::string new_puzzle_solved_message = "You use the keycard to open the door.";
  new_puzzle.setPuzzleSolvedMessage(new_puzzle_solved_message);

  new_puzzle.setPuzzleID(1);
  new_puzzle.setRequiredItemID(25);
  new_puzzle.setPowerRequired(true);

  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(3);
  new_exits = new Exit[new_room.getNumberExits()];
  for(int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      new_exits[i] = Exit(GameObject(0, new_background[new_grid_size_x / 2].getMyLocation()), 0, 25, 1, true);
    }
    if (i == 1)
    {
      new_exits[i] = Exit(GameObject(1,  new_background[139].getMyLocation()), 1, 2, 0, false);
    }
    if (i == 2)
    {
      new_exits[i] = Exit(GameObject(3,  new_background[120].getMyLocation()), 2, 0, 0, false);
    }

  }
  new_room.setMyExits(new_exits);


  visited_rooms[1] = new_room;

}

