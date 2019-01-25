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

  ASGE::Sprite* new_sprites[16];
  for (int i = 0; i < 16; i++)
  {
    new_sprites[i] = renderer->createRawSprite();
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
    new_sprites[i]->loadTexture(texture);
    new_sprites[i]->height(GRID_SIZE);
    new_sprites[i]->width(GRID_SIZE);
    new_sprites[i]->xPos(GAME_WIDTH / 2 - GRID_SIZE / 2);
    new_sprites[i]->yPos(GAME_HEIGHT / 2  -GRID_SIZE / 2);
  }
  player_one.setupPlayer(new_sprites);
  setupRooms();


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


  game_state = SPLASH_SCREEN;
  main_menu_option = NEW_GAME;
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

  else if(game_state == IN_GAME)
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
        ASGE::Sprite* new_sprite = player_one.getInventory(inventory_menu_option).
            getMyGameObject().getMySprite();
        new_sprite->height(GRID_SIZE);
        new_sprite->width(GRID_SIZE);
        new_sprite->xPos(new_location.x);
        new_sprite->yPos(new_location.y);
        Item new_item = player_one.getInventory(inventory_menu_option);
        GameObject new_gameobject;
        new_gameobject.setMySprite(new_sprite);
        new_gameobject.setMyLocation(new_location);

        new_item.setMyGameObject(new_gameobject);
        current_room.addItem(new_item);
        new_gameobject.setMySprite(nullptr);
        new_item.setMyGameObject(new_gameobject);
        new_item.setItemID(-1);
        new_item.setItemDescription("");
        new_item.setItemName("");
        player_one.addToInventory(new_item, inventory_menu_option);

      }
    }
  }


  else if(game_state == PAUSE)
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

  else if(game_state == GAME_OVER)
  {
    if (key->key == ASGE::KEYS::KEY_ESCAPE)
    {
      signalExit();
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

    if(current_room.checkCollisions(&player_one, &text_to_display, &game_state))
    {
      player_one.setMoving(false);
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
    renderer->renderSprite(*current_room.getMyBackground()[i].getMySprite());

  }

  for (int i = 0; i < (((current_room.getMyGridsizeX() + current_room.getMyGridsizeY()) * 2) + 4 ); i++)
  {
    renderer->renderSprite(*current_room.getMyWalls()[i].getMySprite());
  }

  GameObject player = player_one.getPlayerGameobject();
  renderer->renderSprite(*player.getMySprite());


  for (int i = 0; i < (current_room.getMyGridsizeX()*
                       current_room.getMyGridsizeY()); i++)
  {
    if ( current_room.getMyForeground()[i].getMySprite() != nullptr)
    {
      renderer->renderSprite(* current_room.getMyForeground()[i].getMySprite());
    }

  }


  if (current_room.getMyPuzzle().getNumberSwitches() > 0)
  {
    for(int i = 0; i < current_room.getMyPuzzle().getNumberSwitches(); i++)
    {
      if (current_room.getMyPuzzle().getMySwitches()[i].isOn())
      {
        renderer->renderSprite(*current_room.getMyPuzzle().getMySwitches()[i].getMyOnGameobject().getMySprite());
      }
      else
      {
        renderer->renderSprite(*current_room.getMyPuzzle().getMySwitches()[i].getMyOffGameobject().getMySprite());
      }

    }
  }

  for(int i = 0; i < current_room.getMyPuzzle().getNumberMovables(); i++)
  {
    renderer->renderSprite(*current_room.getMyPuzzle().getMyMovables()[i].getMySprite());
  }



  for(int i = 0; i < current_room.getNumberItems(); i++)
  {
    renderer->renderSprite(*current_room.getMyItems()[i].getMyGameObject().getMySprite());
  }
  for(int i = 0; i < current_room.getNumberClues(); i++)
  {
    renderer->renderSprite(*current_room.getMyClues()[i].getMyGameObject().getMySprite());
  }

  for(int i = 0; i < current_room.getNumberExits(); i++)
  {
    renderer->renderSprite(*current_room.getMyExits()[i].getMyExitGameobject().getMySprite());
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

      player_one.getInventory(i).getMyGameObject().getMySprite()->height(
          GRID_SIZE * 2);
      player_one.getInventory(i).getMyGameObject().getMySprite()->width(
          GRID_SIZE * 2);
      player_one.getInventory(i).getMyGameObject().getMySprite()->xPos(new_x);
      player_one.getInventory(i).getMyGameObject().getMySprite()->yPos(new_y);

      renderer->renderSprite(
          *player_one.getInventory(i).getMyGameObject().getMySprite());
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
void MyGame::setupRooms()
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
  GameObject* null_gameobject = nullptr;

  new_room.setRoomID(0);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_background = new GameObject[(new_grid_size_x * new_grid_size_y)];
  float left_side = static_cast<float>(GAME_WIDTH * 0.5 -
             (GRID_SIZE * (static_cast<float>(new_grid_size_x) * 0.5f)));
  float top_side = static_cast<float>(GAME_HEIGHT * 0.5 -
             (GRID_SIZE * (static_cast<float>(new_grid_size_y) * 0.5f)));
  for (int i = 0; i < (new_grid_size_x * new_grid_size_y); i++)
  {
    ASGE::Sprite* new_sprite = new_background[i].getMySprite();
    Point2D new_location;
    new_sprite = renderer->createRawSprite();
    new_sprite->loadTexture("/data/Room_Sprites/Sci_FI_Sheet_One/tile042.png");
    new_sprite->width(GRID_SIZE);
    new_sprite->height(GRID_SIZE);
    new_sprite->xPos(left_side);
    new_sprite->yPos(top_side);
    new_location.x = new_sprite->xPos();
    new_location.y = new_sprite->yPos();
    new_background[i].setMySprite(new_sprite);
    new_background[i].setMyLocation(new_location);
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
    if (i == 8)
    {
      ASGE::Sprite* new_sprite = new_foreground[i].getMySprite();
      Point2D new_location;
      new_sprite = renderer->createRawSprite();
      new_sprite->loadTexture
             ("/data/Room_Sprites/Sci_FI_Sheet_One/tile094.png");
      new_sprite->width(GRID_SIZE);
      new_sprite->height(GRID_SIZE);
      new_sprite->xPos(left_side);
      new_sprite->yPos(top_side - GRID_SIZE );
      new_location.x = new_sprite->xPos();
      new_location.y = new_sprite->yPos();
      new_foreground[i].setMySprite(new_sprite);
      new_foreground[i].setMyLocation(new_location);
    }
    else if (i == 9)
    {
      ASGE::Sprite* new_sprite = new_foreground[i].getMySprite();
      Point2D new_location;
      new_sprite = renderer->createRawSprite();
      new_sprite->loadTexture
              ("/data/Room_Sprites/Sci_FI_Sheet_One/tile095.png");
      new_sprite->width(GRID_SIZE);
      new_sprite->height(GRID_SIZE);
      new_sprite->xPos(left_side);
      new_sprite->yPos(top_side - GRID_SIZE );
      new_location.x = new_sprite->xPos();
      new_location.y = new_sprite->yPos();
      new_foreground[i].setMySprite(new_sprite);
      new_foreground[i].setMyLocation(new_location);
    }
    else if (i == 23)
    {
      ASGE::Sprite* new_sprite = new_foreground[i].getMySprite();
      Point2D new_location;
      new_sprite = renderer->createRawSprite();
      new_sprite->loadTexture
                    ("/data/Room_Sprites/Sci_FI_Sheet_One/tile110.png");
      new_sprite->width(GRID_SIZE);
      new_sprite->height(GRID_SIZE);
      new_sprite->xPos(left_side);
      new_sprite->yPos(top_side - GRID_SIZE );
      new_location.x = new_sprite->xPos();
      new_location.y = new_sprite->yPos();
      new_foreground[i].setMySprite(new_sprite);
      new_foreground[i].setMyLocation(new_location);
    }
    else if (i == 24)
    {
      ASGE::Sprite* new_sprite = new_foreground[i].getMySprite();
      Point2D new_location;
      new_sprite = renderer->createRawSprite();
      new_sprite->loadTexture
                    ("/data/Room_Sprites/Sci_FI_Sheet_One/tile111.png");
      new_sprite->width(GRID_SIZE);
      new_sprite->height(GRID_SIZE);
      new_sprite->xPos(left_side);
      new_sprite->yPos(top_side - GRID_SIZE );
      new_location.x = new_sprite->xPos();
      new_location.y = new_sprite->yPos();
      new_foreground[i].setMySprite(new_sprite);
      new_foreground[i].setMyLocation(new_location);
    }
    else if (i == 30)
    {
      ASGE::Sprite* new_sprite = new_foreground[i].getMySprite();
      Point2D new_location;
      new_sprite = renderer->createRawSprite();
      new_sprite->loadTexture
                    ("/data/Room_Sprites/Sci_FI_Sheet_One/tile151.png");
      new_sprite->width(GRID_SIZE);
      new_sprite->height(GRID_SIZE);
      new_sprite->xPos(left_side);
      new_sprite->yPos(top_side);
      new_location.x = new_sprite->xPos();
      new_location.y = new_sprite->yPos();
      new_foreground[i].setMySprite(new_sprite);
      new_foreground[i].setMyLocation(new_location);
    }
    else if (i == 45)
    {
      ASGE::Sprite* new_sprite = new_foreground[i].getMySprite();
      Point2D new_location;
      new_sprite = renderer->createRawSprite();
      new_sprite->loadTexture
                    ("/data/Room_Sprites/Sci_FI_Sheet_One/tile085.png");
      new_sprite->width(GRID_SIZE);
      new_sprite->height(GRID_SIZE);
      new_sprite->xPos(left_side);
      new_sprite->yPos(top_side);
      new_location.x = new_sprite->xPos();
      new_location.y = new_sprite->yPos();
      new_foreground[i].setMySprite(new_sprite);
      new_foreground[i].setMyLocation(new_location);
    }
    else if (i == 60)
    {
      ASGE::Sprite* new_sprite = new_foreground[i].getMySprite();
      Point2D new_location;
      new_sprite = renderer->createRawSprite();
      new_sprite->loadTexture
                    ("/data/Room_Sprites/Sci_FI_Sheet_One/tile167.png");
      new_sprite->width(GRID_SIZE);
      new_sprite->height(GRID_SIZE);
      new_sprite->xPos(left_side);
      new_sprite->yPos(top_side);
      new_location.x = new_sprite->xPos();
      new_location.y = new_sprite->yPos();
      new_foreground[i].setMySprite(new_sprite);
      new_foreground[i].setMyLocation(new_location);
    }
    else if (i == 75)
    {
      ASGE::Sprite* new_sprite = new_foreground[i].getMySprite();
      Point2D new_location;
      new_sprite = renderer->createRawSprite();
      new_sprite->loadTexture
                    ("/data/Room_Sprites/Sci_FI_Sheet_One/tile183.png");
      new_sprite->width(GRID_SIZE);
      new_sprite->height(GRID_SIZE);
      new_sprite->xPos(left_side);
      new_sprite->yPos(top_side);
      new_location.x = new_sprite->xPos();
      new_location.y = new_sprite->yPos();
      new_foreground[i].setMySprite(new_sprite);
      new_foreground[i].setMyLocation(new_location);
    }
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
      ASGE::Sprite* new_sprite = new_walls[i].getMySprite();
      Point2D new_location;
      new_sprite = renderer->createRawSprite();
      new_sprite->loadTexture
                    ("/data/Room_Sprites/Walls/tile019.png");
      new_sprite->width(GRID_SIZE);
      new_sprite->height(GRID_SIZE);
      new_sprite->xPos(wall_left_side);
      new_sprite->yPos(wall_top_side);
      new_location.x = new_sprite->xPos();
      new_location.y = new_sprite->yPos();
      new_walls[i].setMySprite(new_sprite);
      new_walls[i].setMyLocation(new_location);
    }
    else if (i > 0 &&
             i < 16)
    {
      wall_left_side += GRID_SIZE;
      ASGE::Sprite* new_sprite = new_walls[i].getMySprite();
      Point2D new_location;
      new_sprite = renderer->createRawSprite();
      new_sprite->loadTexture
                    ("/data/Room_Sprites/Walls/tile019.png");
      new_sprite->width(GRID_SIZE);
      new_sprite->height(GRID_SIZE);
      new_sprite->xPos(wall_left_side);
      new_sprite->yPos(wall_top_side);
      new_location.x = new_sprite->xPos();
      new_location.y = new_sprite->yPos();
      new_walls[i].setMySprite(new_sprite);
      new_walls[i].setMyLocation(new_location);
    }
    else if (i == 16)
    {


      wall_left_side += GRID_SIZE;
      ASGE::Sprite* new_sprite = new_walls[i].getMySprite();
      Point2D new_location;
      new_sprite = renderer->createRawSprite();
      new_sprite->loadTexture
                    ("/data/Room_Sprites/Walls/tile019.png");
      new_sprite->width(GRID_SIZE);
      new_sprite->height(GRID_SIZE);
      new_sprite->xPos(wall_left_side);
      new_sprite->yPos(wall_top_side);
      new_location.x = new_sprite->xPos();
      new_location.y = new_sprite->yPos();
      new_walls[i].setMySprite(new_sprite);
      new_walls[i].setMyLocation(new_location);
    }
    else if (i > 16 &&
             i < 25)
    {
      wall_left_side = static_cast<float>((GAME_WIDTH ) * 0.5 - (GRID_SIZE *
             (static_cast<float>(new_grid_size_x) * 0.5f))- GRID_SIZE);
      wall_top_side += GRID_SIZE;
      ASGE::Sprite* new_sprite = new_walls[i].getMySprite();
      Point2D new_location;
      new_sprite = renderer->createRawSprite();
      new_sprite->loadTexture
                    ("/data/Room_Sprites/Walls/tile019.png");
      new_sprite->width(GRID_SIZE);
      new_sprite->height(GRID_SIZE);
      new_sprite->xPos(wall_left_side);
      new_sprite->yPos(wall_top_side);
      new_location.x = new_sprite->xPos();
      new_location.y = new_sprite->yPos();
      new_walls[i].setMySprite(new_sprite);
      new_walls[i].setMyLocation(new_location);
    }

    else if (i == 25)
    {
      wall_top_side = static_cast<float>((GAME_HEIGHT) * 0.5 -
        (GRID_SIZE * (static_cast<float>(new_grid_size_y) * 0.5f)));

      wall_left_side = static_cast<float>((GAME_WIDTH * 0.5) + (GRID_SIZE *
             (static_cast<float>(new_grid_size_x) * 0.5f)) );
      ASGE::Sprite* new_sprite = new_walls[i].getMySprite();
      Point2D new_location;
      new_sprite = renderer->createRawSprite();
      new_sprite->loadTexture
                    ("/data/Room_Sprites/Walls/tile019.png");
      new_sprite->width(GRID_SIZE);
      new_sprite->height(GRID_SIZE);
      new_sprite->xPos(wall_left_side);
      new_sprite->yPos(wall_top_side);
      new_location.x = new_sprite->xPos();
      new_location.y = new_sprite->yPos();
      new_walls[i].setMySprite(new_sprite);
      new_walls[i].setMyLocation(new_location);
    }
    else if (i > 25 &&
             i < 32)
    {
      wall_top_side += GRID_SIZE;
      ASGE::Sprite* new_sprite = new_walls[i].getMySprite();
      Point2D new_location;
      new_sprite = renderer->createRawSprite();
      new_sprite->loadTexture
                    ("/data/Room_Sprites/Walls/tile019.png");
      new_sprite->width(GRID_SIZE);
      new_sprite->height(GRID_SIZE);
      new_sprite->xPos(wall_left_side);
      new_sprite->yPos(wall_top_side);
      new_location.x = new_sprite->xPos();
      new_location.y = new_sprite->yPos();
      new_walls[i].setMySprite(new_sprite);
      new_walls[i].setMyLocation(new_location);

    }
    else if (i == 32)
    {
      wall_left_side = static_cast<float>((GAME_WIDTH ) * 0.5 -
            (GRID_SIZE * (static_cast<float>(new_grid_size_x) * 0.5f)));
      wall_top_side += GRID_SIZE;
      ASGE::Sprite* new_sprite = new_walls[i].getMySprite();
      Point2D new_location;
      new_sprite = renderer->createRawSprite();
      new_sprite->loadTexture
                    ("/data/Room_Sprites/Walls/tile019.png");
      new_sprite->width(GRID_SIZE);
      new_sprite->height(GRID_SIZE);
      new_sprite->xPos(wall_left_side);
      new_sprite->yPos(wall_top_side);
      new_location.x = new_sprite->xPos();
      new_location.y = new_sprite->yPos();
      new_walls[i].setMySprite(new_sprite);
      new_walls[i].setMyLocation(new_location);
      wall_left_side += GRID_SIZE;
    }

    else if (i > 32 &&
             i < 48)
    {
      ASGE::Sprite* new_sprite = new_walls[i].getMySprite();
      Point2D new_location;
      new_sprite = renderer->createRawSprite();
      new_sprite->loadTexture
                    ("/data/Room_Sprites/Walls/tile019.png");
      new_sprite->width(GRID_SIZE);
      new_sprite->height(GRID_SIZE);
      new_sprite->xPos(wall_left_side);
      new_sprite->yPos(wall_top_side);
      new_location.x = new_sprite->xPos();
      new_location.y = new_sprite->yPos();
      new_walls[i].setMySprite(new_sprite);
      new_walls[i].setMyLocation(new_location);
      wall_left_side += GRID_SIZE;
    }
    else if (i == 48)
    {
      ASGE::Sprite* new_sprite = new_walls[i].getMySprite();
      Point2D new_location;
      new_sprite = renderer->createRawSprite();
      new_sprite->loadTexture
                    ("/data/Room_Sprites/Walls/tile019.png");
      new_sprite->width(GRID_SIZE);
      new_sprite->height(GRID_SIZE);
      new_sprite->xPos(wall_left_side);
      new_sprite->yPos(wall_top_side);
      new_location.x = new_sprite->xPos();
      new_location.y = new_sprite->yPos();
      new_walls[i].setMySprite(new_sprite);
      new_walls[i].setMyLocation(new_location);
    }


  }
  new_room.setMyWalls(new_walls);

  new_clues = new Clue[1];
  new_clues->setMyGameObject(new_foreground[24]);
  new_clues->setClueID(1);
  new_clues->setItemDescription("There is no power.");
  new_room.setNumberClues(1);
  new_room.setMyClues(new_clues);

  new_items = new Item;
  GameObject new_gameobject = new_background[90];
  ASGE::Sprite* new_sprite = new_gameobject.getMySprite();
  Point2D new_location;
  new_location = new_gameobject.getMyLocation();
  new_sprite = renderer->createRawSprite();
  new_sprite->loadTexture
                ("/data/Room_Sprites/Objects/Item_Sheet_One/tile024.png");
  new_sprite->xPos(new_location.x);
  new_sprite->yPos(new_location.y);
  new_gameobject.setMySprite(new_sprite);
  new_gameobject.setMyLocation(new_location);
  new_items->setMyGameObject(new_gameobject);
  new_items->setItemID(0);
  new_items->setItemDescription("You found a screwdriver");
  new_items->setItemName("Screwdriver");
  new_room.setMyItems(new_items);
  new_room.setNumberItems(1);

  int* new_linked_exits = nullptr;
  new_linked_exits = new int[1];
  new_linked_exits[0] = 0;

  Switch* new_switches = nullptr;

  bool* new_target_switch_states = nullptr;
  Point2D* new_target_movable_locations = nullptr;

  std::string new_puzzle_solved_message = "You use the screwdriver to "
                                          "unlock the door.";

  new_puzzle.setPuzzleID(0);
  new_puzzle.setNumberMovables(0);
  new_puzzle.setMyMovables(null_gameobject);
  new_puzzle.setTargetMovableLocations(new_target_movable_locations);
  new_puzzle.setNumberSwitches(0);
  new_puzzle.setTargetSwitchStates(new_target_switch_states);
  new_puzzle.setMySwitches(new_switches);
  new_puzzle.setNumberLinkedExits(1);
  new_puzzle.setLinkedExits(new_linked_exits);
  new_puzzle.setRequiredItemID(0);
  new_puzzle.setPuzzleSolvedMessage(new_puzzle_solved_message);
  new_room.setMyPuzzle(new_puzzle);

  GameObject new_exit_gameobject;
  ASGE::Sprite* new_exit_sprite;
  new_exit_sprite = renderer->createRawSprite();
  new_exit_sprite->loadTexture
                ("/data/Room_Sprites/Sci_FI_Sheet_One/tile047.png");
  Point2D new_exit_location = new_background[74].getMyLocation();
  new_exit_sprite->height(GRID_SIZE);
  new_exit_sprite->width(GRID_SIZE);
  new_exit_sprite->xPos(new_exit_location.x);
  new_exit_sprite->yPos(new_exit_location.y);

  new_exit_gameobject.setMySprite(new_exit_sprite);
  new_exit_gameobject.setMyLocation(new_exit_location);

  new_exits = new Exit;
  new_exits->setMyExitGameobject(new_exit_gameobject);
  new_exits->setConnectedExitID(1);
  new_exits->setConnectedRoomID(1);
  new_exits->setLocked(true);
  new_exits->setExitID(0);
  new_room.setMyExits(new_exits);
  new_room.setNumberExits(1);
  current_room = new_room;
}