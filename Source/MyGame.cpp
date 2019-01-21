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
#include <Engine/Texture.h>

#include "MyGame.h"

bool MyGame::init()
{
  game_name = "ContAInment";

  game_height = 800;
  game_width = 1440;
  if (!initAPI())
  {
    return false;
  }

  setupGame();
  setupPlayer();

  inputs->use_threads = false;

  key_callback_id = inputs->addCallbackFnc(ASGE::E_KEY, &MyGame::keyHandler, this);
  toggleFPS();

  return true;
}

void MyGame::setupGame()
{
  splash_screen = renderer->createRawSprite();
  splash_screen->loadTexture("/data/Splash.png");
  splash_screen->width((GAME_WIDTH * 0.5f));
  splash_screen->height((GAME_HEIGHT * 0.5));
  splash_screen->xPos((GAME_WIDTH * 0.5f) - (splash_screen->width() * 0.5f));
  splash_screen->yPos((GAME_HEIGHT * 0.5f) - (splash_screen->height() * 0.5f));
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

  game_state = SPLASH_SCREEN;
  main_menu_option = NEW_GAME;
}

void MyGame::setupPlayer()
{
  int* new_clues = new int[0];
  player_one.setCluesFound(new_clues);
  player_one.setDirection(SOUTH);
  player_one.setMoving(false);
  player_one.setNumberCluesFound(0);
  player_one.setNumberPuzzlesSolved(0);
  player_one.setPuzzlesSolved(new_clues);
  player_one.setSpriteIndex(0);

  ASGE::Sprite* new_sprites[16];
  for (int i = 0; i < 16; i++)
  {
    new_sprites[i] = renderer->createRawSprite();
    std::string texture = "/data/ScientistSprites/tile0";
    switch (i)
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
    new_sprites[i]->yPos(GAME_HEIGHT / 2 - GRID_SIZE / 2);
  }
  player_one.setPlayerSprites(new_sprites);
  GameObject new_player_gameobject;
  new_player_gameobject.setMySprite(new_sprites[0]);
  Point2D new_location;
  new_location.x = new_sprites[0]->xPos();
  new_location.y = new_sprites[0]->yPos();
  new_player_gameobject.setMyLocation(new_location);
  player_one.setPlayerGameobject(new_player_gameobject);
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

  if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_PRESSED &&
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
  else if (game_state == MAIN_MENU)
  {
    if (key->key == ASGE::KEYS::KEY_ESCAPE)
    {
      signalExit();
    }
    else if ((key->key == ASGE::KEYS::KEY_W || key->key == ASGE::KEYS::KEY_UP) &&
             key->action == ASGE::KEYS::KEY_PRESSED)
    {
      main_menu_option--;
      if (main_menu_option < NEW_GAME)
      {
        main_menu_option = EXIT_GAME;
      }
    }
    else if ((key->key == ASGE::KEYS::KEY_S || key->key == ASGE::KEYS::KEY_DOWN) &&
             key->action == ASGE::KEYS::KEY_PRESSED)
    {
      main_menu_option++;
      if (main_menu_option > EXIT_GAME)
      {
        main_menu_option = NEW_GAME;
      }
    }
    else if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_PRESSED)
    {
      switch (main_menu_option)
      {
        case NEW_GAME:
          game_state = IN_GAME;
          break;
        case LOAD_GAME:
          game_state = IN_GAME;
          break;
        case EXIT_GAME:
          signalExit();
          break;
      }
    }
  }

  else if (game_state == IN_GAME)
  {
    if ((key->key == ASGE::KEYS::KEY_W || key->key == ASGE::KEYS::KEY_UP) &&
        key->action == ASGE::KEYS::KEY_REPEATED)
    {
      player_one.setMoving(true);
      player_one.setDirection(NORTH);
    }
    else if ((key->key == ASGE::KEYS::KEY_A || key->key == ASGE::KEYS::KEY_LEFT) &&
             key->action == ASGE::KEYS::KEY_REPEATED)
    {
      player_one.setMoving(true);
      player_one.setDirection(WEST);
    }
    else if ((key->key == ASGE::KEYS::KEY_S || key->key == ASGE::KEYS::KEY_DOWN) &&
             key->action == ASGE::KEYS::KEY_REPEATED)
    {
      player_one.setMoving(true);
      player_one.setDirection(SOUTH);
    }
    else if ((key->key == ASGE::KEYS::KEY_D || key->key == ASGE::KEYS::KEY_RIGHT) &&
             key->action == ASGE::KEYS::KEY_REPEATED)
    {
      player_one.setMoving(true);
      player_one.setDirection(EAST);
    }
    else
    {
      player_one.setMoving(false);
    }
  }

  else if (game_state == INVENTORY)
  {
  }

  else if (game_state == PAUSE)
  {
  }

  else if (game_state == GAME_OVER)
  {
    if (key->key == ASGE::KEYS::KEY_ESCAPE)
    {
      signalExit();
    }
  }
}

// cppcheck-suppress unusedFunction
void MyGame::update(const ASGE::GameTime& game_time)
{
  auto dt_sec = game_time.delta_time.count() / 1000.0f;
  if (game_state == SPLASH_SCREEN)
  {
    splash_screen->width(splash_screen->width() +
                         ((GAME_WIDTH * 0.5f) * 0.3f) * static_cast<float>(dt_sec));
    splash_screen->height(splash_screen->height() +
                          ((GAME_HEIGHT * 0.5f) * 0.3f) * static_cast<float>(dt_sec));
    splash_screen->xPos((GAME_WIDTH * 0.5f) - (splash_screen->width() * 0.5f));
    splash_screen->yPos((GAME_HEIGHT * 0.5f) - (splash_screen->height() * 0.5f));
    if (splash_screen->xPos() < 0.f)
    {
      game_state = MAIN_MENU;
    }
  }
  else if (game_state == IN_GAME)
  {
    animation_counter += dt_sec;
    if (player_one.isMoving())
    {
      if (animation_counter > 0.15)
      {
        animation_counter = 0.0;
        switch (player_one.getDirection())
        {
          case SOUTH:
            if (player_one.getSpriteIndex() + 1 > 3 || player_one.getSpriteIndex() + 1 < 0)
            {
              player_one.setSpriteIndex(0);
            }
            else
            {
              player_one.setSpriteIndex(player_one.getSpriteIndex() + 1);
            }
            break;
          case EAST:
            if (player_one.getSpriteIndex() + 1 > 11 || player_one.getSpriteIndex() + 1 < 8)
            {
              player_one.setSpriteIndex(8);
            }
            else
            {
              player_one.setSpriteIndex(player_one.getSpriteIndex() + 1);
            }
            break;
          case NORTH:
            if (player_one.getSpriteIndex() + 1 > 15 || player_one.getSpriteIndex() + 1 < 12)
            {
              player_one.setSpriteIndex(12);
            }
            else
            {
              player_one.setSpriteIndex(player_one.getSpriteIndex() + 1);
            }
            break;
          case WEST:
            if (player_one.getSpriteIndex() + 1 > 7 || player_one.getSpriteIndex() + 1 < 4)
            {
              player_one.setSpriteIndex(4);
            }
            else
            {
              player_one.setSpriteIndex(player_one.getSpriteIndex() + 1);
            }
            break;
        }
        GameObject player = player_one.getPlayerGameobject();
        player.setMySprite(player_one.getPlayerSprite(player_one.getSpriteIndex()));
        player_one.setPlayerGameobject(player);
      }
    }
  }
  return;
}

// cppcheck-suppress unusedFunction
void MyGame::render(const ASGE::GameTime& game_time)
{
  switch (game_state)
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

void MyGame::renderSplash()
{
  renderer->setClearColour(ASGE::COLOURS::BLACK);
  renderer->renderSprite(*splash_screen);
}

void MyGame::renderMainMenu()
{
  renderer->setClearColour(ASGE::COLOURS::BLACK);
  renderer->renderSprite(*main_menu);
  main_menu_icon->xPos(450.0f);
  switch (main_menu_option)
  {
    case NEW_GAME:
      main_menu_icon->yPos(315.0f);
      break;
    case LOAD_GAME:
      main_menu_icon->yPos(397.5f);
      break;
    case EXIT_GAME:
      main_menu_icon->yPos(480.0f);
      break;
  }

  renderer->renderSprite(*main_menu_icon);
}

void MyGame::renderInGame()
{
  GameObject player = player_one.getPlayerGameobject();
  renderer->renderSprite(*player.getMySprite());
}

void MyGame::renderGameOver() {}

void MyGame::renderPause() {}
void MyGame::renderInventory() {}