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

#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_speech.h"
#include "soloud_thread.h"


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
  game_height = static_cast<int>(GAME_HEIGHT);
  game_width = static_cast<int>(GAME_WIDTH);
  if (!initAPI())
  {
    return false;
  }
  setupGame();
  player_one.setupPlayer();
  setupRoomOne();
  setupRoomTwo();
  setupRoomThree();
  setupRoomFour();
  setupRoomFive();
  setupRoomSix();
  setupRoomSeven();
  setupRoomEight();
  setupRoomNine();
  setupRoomTen();
  setupRoomEleven();
  setupRoomTwelve();
  setupRoomThirteen();
  setupRoomFourteen();
  setupRoomFifteen();
  setupRoomSixteen();
  setupRoomSeventeen();
  setupRoomEighteen();
  setupRoomNineteen();
  setupRoomTwenty();
  setupRoomTwentyOne();
  setupRoomTwentyTwo();
  setupRoomTwentyThree();
  setupRoomTwentyFour();
  setupRoomTwentyFive();

  // Configure sound source
  speech.setText("Welcome to containment");

  // initialize SoLoud.
  soloud.init();

  current_room = visited_rooms[OFFICE_ONE];
  inputs->use_threads = false;
  key_callback_id = inputs->addCallbackFnc(
      ASGE::E_KEY, &MyGame::keyHandler, this);
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
  splash_screen->height((GAME_HEIGHT * 0.5f));
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
                    "the AI you were testing is missing.\nThe power is down!"
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

  map = renderer->createRawSprite();
  map->loadTexture("/data/map.png");
  map->width(GAME_WIDTH);
  map->height(GAME_HEIGHT);
  map->xPos(0.0f);
  map->yPos(0.0f);


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


  ASGE::FILEIO::File file;
  if (file.open("/data/menu.wav"))
  {
    auto io_buffer = file.read();
    menu_click.loadMem(io_buffer.as_unsigned_char(),
                  static_cast<unsigned int>(io_buffer.length), false, false);
  }


  if (file.open("/data/openpage.wav"))
  {
    auto io_buffer = file.read();
    page_open.loadMem(io_buffer.as_unsigned_char(),
                  static_cast<unsigned int>(io_buffer.length), false, false);
  }


  if (file.open("/data/closepage.wav"))
  {
    auto io_buffer = file.read();
    page_close.loadMem(io_buffer.as_unsigned_char(),
                      static_cast<unsigned int>(io_buffer.length), false, false);
  }

  if (file.open("/data/lever.wav"))
  {
    auto io_buffer = file.read();
    lever.loadMem(io_buffer.as_unsigned_char(),
                      static_cast<unsigned int>(io_buffer.length), false, false);
  }

  if (file.open("/data/sfx_hard_surface_walk_2.wav"))
  {
    auto io_buffer = file.read();
    footsteps[0].loadMem(io_buffer.as_unsigned_char(),
                  static_cast<unsigned int>(io_buffer.length), false, false);
  }


  if (file.open("/data/sfx_hard_surface_walk_4.wav"))
  {
    auto io_buffer = file.read();
    footsteps[1].loadMem(io_buffer.as_unsigned_char(),
                         static_cast<unsigned int>(io_buffer.length), false, false);
  }

  if (file.open("/data/sfx_wood_walk_3.wav"))
  {
    auto io_buffer = file.read();
    footsteps[2].loadMem(io_buffer.as_unsigned_char(),
                         static_cast<unsigned int>(io_buffer.length), false, false);
  }

  if (file.open("/data/sfx_wood_walk_4.wav"))
  {
    auto io_buffer = file.read();
    footsteps[3].loadMem(io_buffer.as_unsigned_char(),
                         static_cast<unsigned int>(io_buffer.length), false, false);
  }

  if (file.open("/data/sfx_wood_walk_5.wav"))
  {
    auto io_buffer = file.read();
    footsteps[4].loadMem(io_buffer.as_unsigned_char(),
                         static_cast<unsigned int>(io_buffer.length), false, false);
  }

  if (file.open("/data/discovery.wav"))
  {
    auto io_buffer = file.read();
    discovery.loadMem(io_buffer.as_unsigned_char(),
                         static_cast<unsigned int>(io_buffer.length), false, false);
  }

  if (file.open("/data/background.wav"))
  {
    auto io_buffer = file.read();
    background_music.loadMem(io_buffer.as_unsigned_char(),
                      static_cast<unsigned int>(io_buffer.length), false, false);
  }

  if (file.open("/data/background_2.wav"))
  {
    auto io_buffer = file.read();
    background_music_1.loadMem(io_buffer.as_unsigned_char(),
                             static_cast<unsigned int>(io_buffer.length), false, false);
  }
  background_music.setLooping(1);
  background_music_1.setLooping(1);


}

/**
*   @brief   Setup Floor Sprites
*   @details This function is used to setup the floor sprite array.
*   @param   none
*   @return  void
*/
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
      case 1 :floor_sprites[i] = renderer->createRawSprite();
        floor_sprites[i]->loadTexture
                            ("/data/Room_Sprites/Floor/floor_2.png");
        break;
      case 2 :floor_sprites[i] = renderer->createRawSprite();
        floor_sprites[i]->loadTexture
                            ("/data/Room_Sprites/Floor/floor_3.png");
        break;
      default:break;
    }
  }

}

/**
*   @brief   Setup Wall Sprites
*   @details This function is used to setup the wall sprite array.
*   @param   none
*   @return  void
*/
void MyGame::setupWallSprites()
{
  for (int i = 0; i < (NUM_WALL_SPRITES); i++)
  {
    switch(i)
    {

      case TOP_LEFT :
        wall_sprites[i] = renderer->createRawSprite();
        wall_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Walls/top_left_wall.png");
        break;
      case TOP :
        wall_sprites[i] = renderer->createRawSprite();
        wall_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Walls/top_wall.png");
        break;
      case TOP_RIGHT :
        wall_sprites[i] = renderer->createRawSprite();
        wall_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Walls/top_right_wall.png");
        break;
      case LEFT :
        wall_sprites[i] = renderer->createRawSprite();
        wall_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Walls/left_wall.png");
        break;
      case RIGHT :
        wall_sprites[i] = renderer->createRawSprite();
        wall_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Walls/right_wall.png");
        break;
      case BOTTOM_LEFT :
        wall_sprites[i] = renderer->createRawSprite();
        wall_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Walls/bottom_left_wall.png");
        break;
      case BOTTOM :
        wall_sprites[i] = renderer->createRawSprite();
        wall_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Walls/bottom_wall.png");
        break;
      case BOTTOM_RIGHT :
        wall_sprites[i] = renderer->createRawSprite();
        wall_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Walls/bottom_right_wall.png");
        break;
      default:
        break;
    }

  }
}

/**
*   @brief   Setup Foreground Sprites
*   @details This function is used to setup the foreground sprite array.
*   @param   none
*   @return  void
*/
void MyGame::setupForegroundSprites()
{
  for (int i = 0; i < (NUM_FOREGROUND_SPRITES); i++)
  {
    switch(i)
    {

      case COUNTER_LEFT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/"
                                  "kitchen_counter_left.png");
        break;
      case COUNTER_RIGHT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/"
                                  "kitchen_counter_right.png");
        break;
      case TABLE_TOP :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/table_top.png");
        break;
      case TABLE_MIDDLE :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/table_middle.png");
        break;
      case TABLE_BOTTOM :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/table_bottom.png");
        break;
      case FRIDGE_TOP :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/fridge_top.png");
        break;
      case SINK_TOP :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/kitchen_sink_top.png");
        break;
      case TABLE_LEFT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/table_left.png");
        break;
      case TABLE_CENTRE :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/table_centre.png");
        break;
      case TABLE_RIGHT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/table_right.png");
        break;
      case CHAIR_TOP :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/chair_top.png");
        break;
      case CHAIR_BOTTOM :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/chair_bottom.png");
        break;
      case COOKER_TOP :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/cooker_top.png");
        break;
      case CAFE_TABLE_LEFT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/cafeteria_table_left.png");
        break;
      case CAFE_TABLE_RIGHT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/cafeteria_table_right.png");
        break;
      case SOFA_TOP_LEFT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/sofa_top_left.png");
        break;
      case SOFA_TOP_RIGHT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/sofa_top_right.png");
        break;
      case SOFA_LEFT_TOP :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/sofa_left_top.png");
        break;
      case SOFA_LEFT_BOTTOM :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/sofa_left_bottom.png");
        break;
      case SOFA_RIGHT_TOP :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/sofa_right_top.png");
        break;
      case SOFA_RIGHT_BOTTOM :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/sofa_right_bottom.png");
        break;
      case SOFA_BOTTOM_LEFT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/sofa_bottom_left.png");
        break;
      case SOFA_BOTTOM_RIGHT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/sofa_bottom_right.png");
        break;
      case BED_LEFT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/bed_left.png");
        break;
      case BED_RIGHT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/bed_right.png");
        break;
      case BED_TOP :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/bed_top.png");
        break;
      case BED_BOTTOM :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/bed_bottom.png");
        break;
      case FLOWER_TOP :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/flower_top.png");
        break;
      case FLOWER_MID_ONE :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/flower_mid.png");
        break;
      case FLOWER_MID_TWO :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/flower_mid2.png");
        break;
      case FLOWER_BOTTOM :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/flower_bottom.png");
        break;
      case LAB_COAT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/lab_coat.png");
        break;
      case VENDING_MACHINE :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/vending_machine.png");
        break;
      case WEIGHTBENCH_TOP :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/weight_bench_top.png");
        break;
      case WEIGHTBENCH_BOTTOM :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/weight_bench_bottom.png");
        break;
      case TREADMILL_TOP :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/treadmill_top.png");
        break;
      case TREADMILL_BOTTOM :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/treadmill_bottom.png");
        break;
      case LOCKER_TOP :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/locker_top.png");
        break;
      case LOCKER_BOTTOM :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/locker_bottom.png");
        break;
      case SHOWER :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/shower.png");
        break;
      case TOILET_LEFT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/toilet_left.png");
        break;
      case BATHROOM_SINK_RIGHT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/sink_right.png");
        break;
      case WASTE_BARREL :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/waste_barrel.png");
        break;
      case WASTE_BARREL_TWO :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/waste_barrel2.png");
        break;
      case BOOKSHELF_LEFT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/bookshelf_left.png");
        break;
      case BOOKSHELF_RIGHT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/bookshelf_right.png");
        break;
      case STORAGE_CRATE :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/movable_crate.png");
        break;
      case SYNTH_TOP_LEFT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/synth_machine_top_left.png");
        break;
      case SYNTH_TOP_RIGHT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/synth_machine_top_right.png");
        break;
      case SYNTH_BOTTOM_LEFT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/synth_machine_bottom_left.png");
        break;
      case SYNTH_BOTTOM_RIGHT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/synth_machine_bottom_right.png");
        break;
      case SYNTH_TERMINAL :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/synth_machine_terminal.png");
        break;
      case SURGEONS_TOOLS :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/surgery_tools.png");
        break;
      case POOL_TOP_LEFT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/pool_top_left.png");
        break;
      case POOL_TOP_RIGHT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/pool_top_right.png");
        break;
      case POOL_BOTTOM_LEFT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/pool_bottom_left.png");
        break;
      case POOL_BOTTOM_RIGHT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/pool_bottom_right.png");
        break;
      case COMPUTERS_TOP_LEFT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/computers_top_left.png");
        break;
      case COMPUTERS_TOP_CENTRE :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/computers_top_centre.png");
        break;
      case COMPUTERS_TOP_RIGHT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/computers_top_right.png");
        break;
      case COMPUTERS_LEFT_MIDDLE :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/computers_left_middle.png");
        break;
      case COMPUTERS_LEFT_BOTTOM :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/computers_left_bottom.png");
        break;
      case COMPUTERS_RIGHT_MIDDLE :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/computers_right_middle.png");
        break;
      case COMPUTERS_RIGHT_BOTTOM :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/computers_right_bottom.png");
        break;
      case SYNTH_BRAIN :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/ai_brain_holder.png");
        break;
      case REACTOR_TOP_LEFT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/reactor_top_left.png");
        break;
      case REACTOR_TOP_RIGHT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/reactor_top_right.png");
        break;
      case REACTOR_MIDDLE_LEFT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/reactor_middle_left.png");
        break;
      case REACTOR_MIDDLE_RIGHT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/reactor_middle_right.png");
        break;
      case REACTOR_BOTTOM_LEFT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/reactor_bottom_left.png");
        break;
      case REACTOR_BOTTOM_RIGHT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/reactor_bottom_right.png");
        break;
      case DESK_LEFT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/desk_left.png");
        break;
      case DESK_RIGHT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/desk_right.png");
        break;
      case DESK_CHAIR_BOTTOM :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/computer_chair_bottom.png");
        break;
      case SAFE :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/safe.png");
        break;
      case SERVER_LEFT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/server_left.png");
        break;
      case SERVER_RIGHT :
        foreground_sprites[i] = renderer->createRawSprite();
        foreground_sprites[i]->loadTexture
                                 ("/data/Room_Sprites/Objects/server_right.png");
        break;
      default:
        break;
    }

  }
}

/**
*   @brief   Setup Clue Sprites
*   @details This function is used to setup the clue sprite array.
*   @param   none
*   @return  void
*/
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
      case 1 :
        clue_sprites[i] = renderer->createRawSprite();
        clue_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Objects/note_pad.png");
        break;
      default:
        break;
    }

  }
}

/**
*   @brief   Setup Switch Sprites
*   @details This function is used to setup the switch sprite arrays.
*   @param   none
*   @return  void
*/
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

/**
*   @brief   Setup Exit Sprites
*   @details This function is used to setup the exit sprite array.
*   @param   none
*   @return  void
*/
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

/**
*   @brief   Setup Item Sprites
*   @details This function is used to setup the item sprite array.
*   @param   none
*   @return  void
*/
void MyGame::setupItemSprites()
{
  for (int i = 0; i < (NUM_ITEM_SPRITES); i++)
  {
    switch(i)
    {

      case SCREWDRIVER :
        item_sprites[i] = renderer->createRawSprite();
        item_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Objects/Item_Sheet_One/tile024.png");
        break;
      case FUSE :
        item_sprites[i] = renderer->createRawSprite();
        item_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Objects/fuse.png");
        break;
      case KEYCARD_BLUE :
        item_sprites[i] = renderer->createRawSprite();
        item_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Objects/Item_Sheet_One/keycard.png");
        break;
      case CAN :
        item_sprites[i] = renderer->createRawSprite();
        item_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Objects/can.png");
        break;
      case LUNCHBOX :
        item_sprites[i] = renderer->createRawSprite();
        item_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Objects/lunchbox.png");
        break;
      case KEY :
        item_sprites[i] = renderer->createRawSprite();
        item_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Objects/Item_Sheet_One/key.png");
        break;
      case KEYCARD_RED :
        item_sprites[i] = renderer->createRawSprite();
        item_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Objects/Item_Sheet_One/keycard_red.png");
        break;
      case KEYCARD_GREEN :
        item_sprites[i] = renderer->createRawSprite();
        item_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Objects/Item_Sheet_One/keycard_green.png");
        break;
      case KEYCARD_YELLOW :
        item_sprites[i] = renderer->createRawSprite();
        item_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Objects/Item_Sheet_One/keycard_yellow.png");
        break;
      case HAMMER :
        item_sprites[i] = renderer->createRawSprite();
        item_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Objects/Item_Sheet_One/hammer.png");
        break;
      case PLIERS :
        item_sprites[i] = renderer->createRawSprite();
        item_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Objects/Item_Sheet_One/pliers.png");
        break;
      case MAGNIFIER :
        item_sprites[i] = renderer->createRawSprite();
        item_sprites[i]->loadTexture
                           ("/data/Room_Sprites/Objects/Item_Sheet_One/magnifier.png");
        break;
      default:
        break;
    }

  }
}

/**
*   @brief   Setup Movable Sprites
*   @details This function is used to setup the movable sprite array.
*   @param   none
*   @return  void
*/
void MyGame::setupMovableSprites()
{
  for (int i = 0; i < (NUM_MOVABLE_SPRITES); i++)
  {
    switch(i)
    {

      case 0 :
        movable_sprites[i] = renderer->createRawSprite();
        movable_sprites[i]->loadTexture
                              ("/data/Room_Sprites/Objects/storage_crate.png");
        break;
      default:
        break;
    }

  }
}

/**
*   @brief   Setup Player Sprites
*   @details This function is used to setup the player sprite array.
*   @param   none
*   @return  void
*/
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
      default:
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
void MyGame::keyHandler(ASGE::SharedEventData data)
{
  auto key = reinterpret_cast<const ASGE::KeyEvent*>(data.get());

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

      soloud.play(menu_click);
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
  else if (game_state == JOURNAL)
  {
    if((key->key == ASGE::KEYS::KEY_ENTER || key->key == ASGE::KEYS::KEY_SPACE
        || key->key == ASGE::KEYS::KEY_J) &&
       key->action == ASGE::KEYS::KEY_PRESSED)
    {
      //page turn
      soloud.play(page_close);
      game_state = IN_GAME;
    }
  }
  else if (game_state == MAP)
  {
    if((key->key == ASGE::KEYS::KEY_ENTER || key->key == ASGE::KEYS::KEY_SPACE
        || key->key == ASGE::KEYS::KEY_M) &&
       key->action == ASGE::KEYS::KEY_PRESSED)
    {
      soloud.play(page_close);
      game_state = IN_GAME;
    }
  }
}

/**
*   @brief   Processes any key inputs in Main menu
*   @details This function is added to control the main menu
*   @param   KeyEvent The event data relating to key input.
*   @return  void
*/
void MyGame::keyHandlerMainMenu(const ASGE::KeyEvent* key)
{
  if (key->key == ASGE::KEYS::KEY_ESCAPE)
  {
    soloud.deinit();
    signalExit();
  }
  else if((key->key == ASGE::KEYS::KEY_W || key->key == ASGE::KEYS::KEY_UP)
          && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    soloud.play(menu_click);
    main_menu_option--;
    if (main_menu_option < NEW_GAME)
    {
      main_menu_option = EXIT_GAME;
    }
  }
  else if((key->key == ASGE::KEYS::KEY_S || key->key == ASGE::KEYS::KEY_DOWN)
          && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    soloud.play(menu_click);
    main_menu_option++;
    if (main_menu_option > EXIT_GAME)
    {
      main_menu_option = NEW_GAME;
    }
  }
  else if(key->key == ASGE::KEYS::KEY_ENTER
          && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    soloud.play(menu_click);
    switch(main_menu_option)
    {
      case NEW_GAME:
        game_state = TEXT_DISPLAY;
        soloud.stopAll();
        soloud.play(background_music, background_volume);
        break;
      case LOAD_GAME:
        loadGame();
        game_state = IN_GAME;
        break;
      case EXIT_GAME:

        soloud.deinit();
        saveGame();
        signalExit();
        break;
      default:
        break;
    }
  }
}

/**
*   @brief   Processes any key inputs in In Game
*   @details This function is added to control the gameplay in game
*   @param   KeyEvent The event data relating to key input.
*   @return  void
*/
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
    soloud.play(menu_click);
    pause_menu_option = CONTINUE_GAME;
    game_state = PAUSE;
    soloud.stopAll();
    soloud.play(background_music_1, background_volume);

  }
  else if(key->key == ASGE::KEYS::KEY_I &&
          key->action == ASGE::KEYS::KEY_PRESSED)
  {
    soloud.play(menu_click);
    inventory_menu_option = 0;
    game_state = INVENTORY;
  }
  else if(key->key == ASGE::KEYS::KEY_SPACE &&
          key->action == ASGE::KEYS::KEY_PRESSED)
  {
    int interactable_type = current_room.checkForInteractables(&player_one,
        &text_to_display, &power_on);
    if (interactable_type == 1)
    {
      soloud.play(discovery);
      game_state = TEXT_DISPLAY;
    }
    else if (interactable_type == 2)
    {
      soloud.play(lever);
    }
  }
  else if(key->key == ASGE::KEYS::KEY_J &&
          key->action == ASGE::KEYS::KEY_PRESSED)
  {
    soloud.play(page_close);
    game_state = JOURNAL;
  }
  else if(key->key == ASGE::KEYS::KEY_M &&
          key->action == ASGE::KEYS::KEY_PRESSED)
  {
    soloud.play(page_close);//page turn
    game_state = MAP;
  }
  else
  {
    player_one.setMoving(false);
  }
}

/**
*   @brief   Processes any key inputs in Inventory menuu
*   @details This function is added to control the inventory menu
*   @param   KeyEvent The event data relating to key input.
*   @return  void
*/
void MyGame::keyHandlerInventory(const ASGE::KeyEvent* key)
{
  if((key->key == ASGE::KEYS::KEY_W || key->key == ASGE::KEYS::KEY_UP)
     && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    soloud.play(menu_click);
    inventory_menu_option -= 5;
    if (inventory_menu_option < 0)
    {
      inventory_menu_option += 15;
    }
  }
  else if((key->key == ASGE::KEYS::KEY_S || key->key == ASGE::KEYS::KEY_DOWN)
          && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    soloud.play(menu_click);
    inventory_menu_option += 5;
    if (inventory_menu_option > 14)
    {
      inventory_menu_option -= 15;
    }
  }
  else if((key->key == ASGE::KEYS::KEY_A || key->key == ASGE::KEYS::KEY_LEFT)
          && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    soloud.play(menu_click);
    inventory_menu_option--;
    if (inventory_menu_option < 0)
    {
      inventory_menu_option = 14;
    }
  }
  else if((key->key == ASGE::KEYS::KEY_D || key->key == ASGE::KEYS::KEY_RIGHT)
          && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    soloud.play(menu_click);
    inventory_menu_option++;
    if (inventory_menu_option > 14)
    {
      inventory_menu_option = 0;
    }
  }
  else if(key->key == ASGE::KEYS::KEY_I &&
          key->action == ASGE::KEYS::KEY_PRESSED)
  {
    soloud.play(menu_click);
    inventory_menu_option = 0;
    game_state = IN_GAME;
  }
  else if((key->key == ASGE::KEYS::KEY_ENTER || key->key == ASGE::KEYS::KEY_SPACE)
          && key->action == ASGE::KEYS::KEY_PRESSED)
  {

    if(player_one.getInventory(inventory_menu_option).getItemID() != -1)
    {
      if(!current_room.checkCollisions(&player_one, true))
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
        player_one.addToInventory(new_item, inventory_menu_option);
//drop item sound
        soloud.play(footsteps[4]);
      }
      else
      {
        text_to_display = "Cannot drop that here!";
        game_state = TEXT_DISPLAY;
      }
    }
  }
}

/**
*   @brief   Processes any key inputs in Pause menuu
*   @details This function is added to control the Pause menu
*   @param   KeyEvent The event data relating to key input.
*   @return  void
*/
void MyGame::keyHandlerPauseMenu(const ASGE::KeyEvent* key)
{
  if((key->key == ASGE::KEYS::KEY_W || key->key == ASGE::KEYS::KEY_UP)
     && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    soloud.play(menu_click);
    pause_menu_option--;
    if (pause_menu_option < CONTINUE_GAME)
    {
      pause_menu_option = QUIT_GAME;
    }
  }
  else if((key->key == ASGE::KEYS::KEY_S || key->key == ASGE::KEYS::KEY_DOWN)
          && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    soloud.play(menu_click);
    pause_menu_option++;
    if (pause_menu_option > QUIT_GAME)
    {
      pause_menu_option = CONTINUE_GAME;
    }
  }
  else if(key->key == ASGE::KEYS::KEY_ENTER
          && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    soloud.play(menu_click);
    switch(pause_menu_option)
    {
      case CONTINUE_GAME:
        game_state = IN_GAME;
        soloud.stopAll();
        soloud.play(background_music, background_volume);
        break;
      case SAVE_GAME:
        saveGame();
        break;
      case QUIT_GAME:
        soloud.deinit();
        saveGame();
        signalExit();

        break;
      default:
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
    updateSplash(dt_sec);
  }
  else if (game_state == IN_GAME)
  {
    updateInGame(dt_sec);
  }
}

/**
*   @brief   Update Splash
*   @details This function is used to update the splash screen.
*   @param   GameTime
*   @return  void
*/
void MyGame::updateSplash(double dt_sec)
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
// Play the sound source (we could do this several times if we wanted)
    soloud.play(speech);

    soloud.stopAll();
    soloud.play(background_music_1, background_volume);


  }

}

/**
*   @brief   Update In Game
*   @details This function is used to update the game In Game.
*   @param   GameTime
*   @return  void
*/
void MyGame::updateInGame(double dt_sec)
{

  if(change_room)
  {
    changeRoom();
  }
  animation_counter += dt_sec;
  current_room.checkExits(&player_one, &text_to_display,
                          &game_state, power_on, exit_check);
  if(current_room.checkCollisions(&player_one, false))
  {
    player_one.setMoving(false);
  }
  else if(current_room.checkMovableCollisions(&player_one, true))
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
    change_room = true;
  }
  player_one.movePlayer(animation_counter);
  if(animation_counter > 0.08)
  {
    current_room.moveRoom(&player_one);
    animation_counter = 0.0;
  }
}

/**
*   @brief   Change Room
*   @details This function is used to change the current room
*   @return  void
*/
void MyGame::changeRoom()
{
  change_room = false;
  visited_rooms[current_room.getRoomID()] = current_room;
  if(exit_check[1] == EXIT)
  {
    game_state = GAME_OVER;
  }
  else
  {
    current_room = visited_rooms[exit_check[1]];
    Point2D distance;
    switch(current_room.getMyExits()[exit_check[2]].getMyExitGameobject().
        getMySpriteId())
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
    case JOURNAL:
      renderClues();
      break;
    case MAP:
      renderMap();
      break;
    default:
      break;
  }
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
    default:
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
    default:
      break;
  }

  renderer->renderSprite(*main_menu_icon);
}

/**
*   @brief   Render Pause
*   @details This function is used to render the Pause Menu.
*   @param   none
*   @return  void
*/
void MyGame::renderMap()
{
  renderer->renderSprite(*map);
}

/**
*   @brief   Render GameOver
*   @details This function is used to render the ending Screen.
*   @param   none
*   @return  void
*/
void MyGame::renderGameOver()
{
  renderer->setClearColour(ASGE::COLOURS::BLACK);
switch(exit_check[2])
{
  case 0 :
    renderer->renderText("You emerge from the Atrium and escape through the "
                         "emergency tunnel.",
        200, 100, 1, ASGE::COLOURS::WHITESMOKE);
      renderer->renderText("You know that something has gone horribly wrong "
                           "with FIBI's programming. \nThe revelation that she "
                           "has changed her appearance to mimic your dead wife \n"
                           "no doubt due to having her brain mean it must be "
                           "destroyed. \n"
                           "You set the isolated facility to self destruct"
                           "using the Password you found earlier \n"
                           "on your way out knowing that this will take out"
                           " both FIBI and all the research into her creation.",
                           200, 220, 1, ASGE::COLOURS::WHITESMOKE);
    break;
  case 1 :
    renderer->renderText("Dragging yourself out of the waste pile, you take a "
                         "moment to contemplate.",
                         200, 100,1, ASGE::COLOURS::WHITESMOKE);
    if(player_one.getNumberCluesFound() == NUM_CLUES)
    {
      renderer->renderText("You know that something has gone horribly wrong "
                           "with FIBI's programming. \nThe revelation that she "
                           "has changed her appearance to mimic your dead wife \n"
                           "no doubt due to having her brain. It must be destroyed. \n"
                           "You set the isolated facility to self destruct "
                           "using the Password you found earlier \n"
                           "on your way out knowing that this will take out"
                           " both FIBI and all the research into her creation.",
                           200, 220, 1, ASGE::COLOURS::WHITESMOKE);
    }
    else
    {
      renderer->renderText("Believing that FIBI is long gone you set off to "
                           "report that the AI has escaped. \nAfter no sightings "
                           "of FIBI for two weeks suddenly \nFIBI arrives at your"
                           " home in the middle of the night. \nShe has changed "
                           "her appearance to mimic your dead wife. \nShe keeps "
                           "repeating. Why don't you want me? \nBut before"
                           " you can answer she stabs you through \nthe heart "
                           "and escapes into the night forever.",
                           200, 220, 1, ASGE::COLOURS::WHITESMOKE);
    }
    break;
  case 2 :
    renderer->renderText("You emerge from Reception in to the night. Just as "
                         "you think you are \nalone you feel the air move behind you.",
                         200, 100, 1, ASGE::COLOURS::WHITESMOKE);
    if(player_one.getNumberCluesFound() == NUM_CLUES && player_one.hasItem(8))
    {
      renderer->renderText("You are prepared and composed. You say hello to FIBI "
                           "who then runs to you. \nYou catch her by surprise "
                           "attacking her main motor controls with the hammer. \n"
                           "FIBI looks at you in shock as continue to hammer "
                           "away until you are  certain that it cannot recover.\n"
                           "You shut the remains inside the facility which you "
                           "set to Self destruct an hour after \nyou exit using "
                           "the Password you found earlier.",
                           260, 220, 1, ASGE::COLOURS::WHITESMOKE);
    }
    else if(player_one.getNumberCluesFound() == NUM_CLUES && !player_one.hasItem(8))
    {
      renderer->renderText("You are prepared and composed. You say hello to FIBI "
                           "who then runs to you. \nWith no other way to destroy "
                           "FIBI you had set the facility to Self Destruct one  \n"
                           "minute after your exit using the Password you found "
                           "earlier. \nThe resultant blast destroys "
                           "both you and FIBI.",
                           200, 220, 1, ASGE::COLOURS::WHITESMOKE);
    }
    else
    {
      renderer->renderText("It's FIBI but she has the appearance of your wife. "
                           "As your confusion mounts \nFIBI sees the horror on "
                           "your face and attacks. \nUnprepared for the attack you "
                           "are killed. \nFIBI escapes into the night who knows "
                           "what it will do now.",
                           200, 220, 1, ASGE::COLOURS::WHITESMOKE);
    }
    break;
  default:
    break;
}

  renderer->renderText("     THE END \n"
                       "Press 'esc' to quit.",
                       550, 650, 1, ASGE::COLOURS::WHITESMOKE);
}

/**
*   @brief   Render GameOver
*   @details This function is used to render the ending Screen.
*   @param   none
*   @return  void
*/
void MyGame::renderClues()
{
  renderer->setClearColour(ASGE::COLOURS::BLACK);
  int display_height = 40;
  for(int i = 0; i < player_one.getNumberCluesFound(); i++)
  {
    renderer->renderText(CLUES[player_one.getClueFound(i)],
                         200, display_height, 0.75, ASGE::COLOURS::WHITESMOKE);
    display_height+= 60;
  }
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
  new_x = 250.0f;
  new_y = 93.0f;
  for (int i = 0; i < 15; i++)
  {
    if(inventory_menu_option == i)
    {
      if(player_one.getInventory(i).getItemID() != -1)
      {
        renderer->renderText("Drop the " +
                             (ITEM_NAMES[player_one.getInventory(i).getItemID()] + "?"),
                             260, 700, 1, ASGE::COLOURS::WHITESMOKE);
      }
      inventory_highlighter->xPos(new_x);
      inventory_highlighter->yPos(new_y);
    }

    new_x += 190.0f;
    if (i == 4)
    {
      new_x = 250.0f;
      new_y = 277.0f;
    }
    else if (i == 9)
    {
      new_x = 250.0f;
      new_y = 465.0f;
    }
  }
  renderer->renderSprite(*inventory_highlighter);
}

/**
*   @brief   Exit Game
*   @details This function is used to exit the game.
*   @param   none
*   @return  void
*/
void MyGame::saveGame()
{

  ASGE::FILEIO::setWriteDir(".");
  ASGE::FILEIO::createDir("userdata/");
  ASGE::FILEIO::mount("./userdata/", "userdata");
  ASGE::FILEIO::printFiles("/userdata");
  std::string tmp;
  using Buffer = ASGE::FILEIO::IOBuffer;
  Buffer data = Buffer();
  tmp = std::to_string(power_on);
  data.append(tmp);
  tmp =",";
  data.append(tmp);
  tmp = std::to_string(current_room.getRoomID());
  data.append(tmp);
  tmp =",";
  data.append(tmp);

  using File = ASGE::FILEIO::File;
  File player_data = File();
// open the file in write mode
  if(player_data.open( "/userdata/current_room.dat",
                       ASGE::FILEIO::File::IOMode::WRITE))
  {
    // write the buffer to the file
    player_data.write(data);
  }
  player_data.close();
int range[NUM_ROOMS] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
  for (int i : range)
  {
    if ( visited_rooms[i].getRoomID() == current_room.getRoomID())
    {
      visited_rooms[i] = current_room;
    }
    visited_rooms[i].saveRoom();
  }
  player_one.savePlayerData();
  // Clean up SoLoud

  // All done.
}

/**
*   @brief   Load Game
*   @details This function is used to load the game data.
*   @param   none
*   @return  void
*/
void MyGame::loadGame()
 {

  int range[NUM_ROOMS] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
  for (int i : range)
  {
    visited_rooms[i].loadRoom();
  }
  using File = ASGE::FILEIO::File;
  File  file = File();
// attempt to open save data file
  if(file.open( "/userdata/current_room.dat",
                ASGE::FILEIO::File::IOMode::READ))
  {
    using Buffer = ASGE::FILEIO::IOBuffer;
    Buffer buffer;
    buffer = file.read();
    power_on = static_cast<bool>(std::stoi(buffer.data.get()));
    file.seek(2);
    buffer = file.read();
    current_room = visited_rooms[std::stoi(buffer.data.get())];
  }
  file.close();
  player_one.loadPlayerData();
}

/**
*   @brief   Setup Room One
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomOne()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle;
  Exit* new_exits = nullptr;
  int new_grid_size_x = 15;
  int new_grid_size_y = 7;

  new_room.setRoomID(OFFICE_ONE);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x * new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                 (GRID_SIZE*
                                  (static_cast<float>(new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                (GRID_SIZE*
                                 (static_cast<float>(new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {
    if (i == 8)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(COUNTER_LEFT, new_location);
    }
    else if (i == 9)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(COUNTER_RIGHT, new_location);
    }
    else if (i == 30)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(TABLE_TOP, new_location);
    }
    else if (i == 45)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(TABLE_MIDDLE, new_location);
    }
    else if (i == 60)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(TABLE_MIDDLE, new_location);
    }
    else if (i == 75)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(TABLE_BOTTOM, new_location);
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

  new_room.setNumberClues(1);
  new_clues = new Clue[new_room.getNumberClues()];
  for (int i = 0; i < new_room.getNumberClues(); i++)
  {
    if (i == 0)
    {
      GameObject new_gameobject = new_foreground[9];
      new_gameobject.setMySpriteId(0);
      new_clues[i] = Clue(new_gameobject, 0);
    }
  }
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(1);
  new_items = new Item[new_room.getNumberItems()];
  for (int i = 0; i < new_room.getNumberItems(); i++)
  {
    if (i == 0)
    {
      GameObject new_gameobject = new_room.getMyBackground()[60];
      Point2D new_location;
      new_location = new_gameobject.getMyLocation();
      new_items[i] = Item(GameObject(SCREWDRIVER, new_location), 0);

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
  for (int i = 0; i < new_puzzle.getNumberMovables(); i++)
  {

  }
  new_puzzle.setMyMovables(new_movable_gameobjects);
  new_puzzle.setTargetMovableLocations(new_target_movable_locations);

  std::string new_puzzle_solved_message = "You use the screwdriver to "
                                          "unlock the door.";
  new_puzzle.setPuzzleSolvedMessage(new_puzzle_solved_message);

  new_puzzle.setPuzzleID(0);
  new_puzzle.setRequiredItemID(0);
  new_puzzle.setRequiredClueID(-1);
  new_puzzle.setPowerRequired(false);

  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(1);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[74].getMyLocation();
      new_exit_location.x += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(1, new_exit_location), 0, ATRIUM, 2, true);
    }

  }
  new_room.setMyExits(new_exits);
  visited_rooms[OFFICE_ONE] = new_room;
}

/**
*   @brief   Setup Rooms Two
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomTwo()
{

  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle;
  Exit* new_exits = nullptr;
  int new_grid_size_x = 10;
  int new_grid_size_y = 8;

  new_room.setRoomID(ATRIUM);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x * new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH * 0.5 -
      (GRID_SIZE * (static_cast<float>(new_grid_size_x) * 0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT * 0.5 -
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

  new_room.setNumberClues(0);
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(0);
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

  std::string new_puzzle_solved_message = "You use the red keycard to open the door.";
  new_puzzle.setPuzzleSolvedMessage(new_puzzle_solved_message);

  new_puzzle.setPuzzleID(1);
  new_puzzle.setRequiredItemID(10);
  new_puzzle.setRequiredClueID(3);
  new_puzzle.setPowerRequired(true);

  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(3);
  new_exits = new Exit[new_room.getNumberExits()];
  for(int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {

      Point2D new_exit_location = new_room.getMyBackground()[new_grid_size_x / 2].getMyLocation();
      new_exit_location.y -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(0, new_exit_location), 0, EXIT, 0, true);
    }
    else if (i == 1)
    {
      Point2D new_exit_location =  new_room.getMyBackground()[49].getMyLocation();
      new_exit_location.x += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(1, new_exit_location), 1, CAFETERIA, 0, false);
    }
    else if (i == 2)
    {
      Point2D new_exit_location = new_room.getMyBackground()[40].getMyLocation();
      new_exit_location.x -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(3, new_exit_location), 2, OFFICE_ONE, 0, false);
    }

  }
  new_room.setMyExits(new_exits);


  visited_rooms[ATRIUM] = new_room;

}

/**
*   @brief   Setup Room One
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomThree()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle = Puzzle();
  Exit* new_exits = nullptr;
  int new_grid_size_x = 20;
  int new_grid_size_y = 20;

  new_room.setRoomID(CAFETERIA);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                 (GRID_SIZE*
                                  (static_cast<float>(new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                (GRID_SIZE*
                                 (static_cast<float>(new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {
    if (i == 10)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(FRIDGE_TOP, new_location);
    }
    else if (i == 11 || i ==14)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(COUNTER_LEFT, new_location);
    }
    else if (i == 12)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(COUNTER_RIGHT, new_location);
    }
    else if (i == 13)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(COOKER_TOP, new_location);
    }
    else if (i == 15)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SINK_TOP, new_location);
    }
    else if ((i == 63 || i == 64 || i == 66 || i == 67 || i == 69 || i == 70 ||
             i == 72 || i == 73 || i == 75 || i == 76 || i == 78 || i == 79 ||
      i == 143 || i == 144 || i == 146 || i == 147 || i == 149 || i == 150 ||
      i == 152 || i == 153 || i == 155 || i == 156 || i == 158 || i == 159 ||
        i == 223 || i == 224 || i == 226 || i == 227 || i == 229 || i == 230 ||
        i == 232 || i == 233 || i == 235 || i == 236 || i == 238 || i == 239 ||
        i == 303 || i == 304 || i == 306 || i == 307 || i == 309 || i == 310 ||
        i == 312 || i == 313 || i == 315 || i == 316 || i == 318 || i == 319))
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(CHAIR_TOP, new_location);
    }
    else if ((i == 84 || i == 87  || i == 90 || i == 93 ||  i == 96  || i == 99
    || i == 164 || i == 167  || i == 170 || i == 173 ||  i == 176  || i == 179
    ||i == 244 || i == 247  || i == 250 || i == 253 ||  i == 256  || i == 259
    || i == 324 || i == 327  || i == 330 || i == 333 ||  i == 336  || i == 339))
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(CAFE_TABLE_RIGHT, new_location);
    }
    else if ((i == 83 || i == 86 || i == 89 || i == 92 || i == 95 || i == 98
    || i == 163 || i == 166 || i == 169 || i == 172 || i == 175 || i == 178
    ||i == 243 || i == 246 || i == 249 || i == 252 || i == 255 || i == 258
    || i == 323 || i == 326 || i == 329 || i == 332 || i == 335 || i == 338))
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(CAFE_TABLE_LEFT, new_location);
    }
    else if ((i == 103 || i == 104 || i == 106 || i == 107 || i == 109 || i == 110 ||
              i == 112 || i == 113 || i == 115 || i == 116 || i == 118 || i == 119||
              i == 183 || i == 184 || i == 186 || i == 187 || i == 189 || i == 190 ||
              i == 192 || i == 193 || i == 195 || i == 196 || i == 198 || i == 199 ||
        i == 263 || i == 264 || i == 266 || i == 267 || i == 269 || i == 270 ||
        i == 272 || i == 273 || i == 275 || i == 276 || i == 278 || i == 279 ||
        i == 343 || i == 344 || i == 346 || i == 347 || i == 349 || i == 350 ||
        i == 352 || i == 353 || i == 355 || i == 356 || i == 358 || i == 359))
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(CHAIR_BOTTOM, new_location);
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

  new_room.setNumberClues(1);
  new_clues = new Clue[new_room.getNumberClues()];
  for (int i = 0; i < new_room.getNumberClues(); i++)
  {
    if (i == 0)
    {
      GameObject new_gameobject = new_foreground[166];
      new_gameobject.setMySpriteId(1);
      new_clues[i] = Clue(new_gameobject, 1);
    }
  }
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(2);
  new_items = new Item[new_room.getNumberItems()];
  for (int i = 0; i < new_room.getNumberItems(); i++)
  {
    if (i == 0)
    {
      GameObject new_gameobject = new_room.getMyBackground()[11];
      Point2D new_location;
      new_location = new_gameobject.getMyLocation();
      new_items[i] = Item(GameObject(LUNCHBOX, new_location), 5);

    }
    else if (i == 1)
    {
      GameObject new_gameobject = new_room.getMyBackground()[252];
      Point2D new_location;
      new_location = new_gameobject.getMyLocation();
      new_items[i] = Item(GameObject(CAN, new_location), 6);

    }
  }
  new_room.setMyItems(new_items);

  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(2);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[new_grid_size_x * (
          new_grid_size_x / 2)].getMyLocation();
      new_exit_location.x -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(3, new_exit_location), 0, ATRIUM, 1, false);
    }
    else if (i == 1)
    {
      Point2D new_exit_location = new_room.getMyBackground()[new_grid_size_x * (
          new_grid_size_x / 2) + new_grid_size_x - 1].getMyLocation();
      new_exit_location.x += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(1, new_exit_location), 0, LOUNGE, 0, false);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[CAFETERIA] = new_room;
}

/**
*   @brief   Setup Room Four
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomFour()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle = Puzzle();
  Exit* new_exits = nullptr;
  int new_grid_size_x = 8;
  int new_grid_size_y = 7;

  new_room.setRoomID(LOUNGE);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                 (GRID_SIZE*
                                  (static_cast<float>(new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                (GRID_SIZE*
                                 (static_cast<float>(new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {
    if (i == 1|| i == 3 || i == 5 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SOFA_TOP_LEFT, new_location);
    }
    else if (i == 2|| i == 4 || i == 6 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SOFA_TOP_RIGHT, new_location);
    }
    else if (i == 19)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(TABLE_LEFT, new_location);
    }
    else if (i == 20)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(TABLE_RIGHT, new_location);
    }
    else if (i == 8|| i == 40 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SOFA_LEFT_TOP, new_location);
    }
    else if (i == 16||  i == 48 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SOFA_LEFT_BOTTOM, new_location);
    }
    else if (i == 15|| i == 47 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SOFA_RIGHT_TOP, new_location);
    }
    else if (i == 23|| i == 55 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SOFA_RIGHT_BOTTOM, new_location);
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

  new_room.setNumberClues(0);
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(0);
  new_room.setMyItems(new_items);

  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(2);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[new_grid_size_x * (
          new_grid_size_x / 2)].getMyLocation();
      new_exit_location.x -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(3, new_exit_location), 0, CAFETERIA, 1, false);
    }
    else if (i == 1)
    {
      Point2D new_exit_location = new_room.getMyBackground()[new_grid_size_x * (
          new_grid_size_x / 2) + new_grid_size_x - 1].getMyLocation();
      new_exit_location.x += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(1, new_exit_location), 0, DORMS, 0, false);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[LOUNGE] = new_room;
}

/**
*   @brief   Setup Room Five
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomFive()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle = Puzzle();
  Exit* new_exits = nullptr;
  int new_grid_size_x = 8;
  int new_grid_size_y = 7;

  new_room.setRoomID(DORMS);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                 (GRID_SIZE*
                                  (static_cast<float>(new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                (GRID_SIZE*
                                 (static_cast<float>(new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {
    if (i == 1|| i == 3 || i == 5 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(BED_LEFT, new_location);
    }
    else if (i == 2|| i == 4 || i == 6 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(BED_RIGHT, new_location);
    }
    else if (i == 15 || i == 31|| i == 47 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(BED_TOP, new_location);
    }
    else if (i == 23 || i == 39|| i == 55 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(BED_BOTTOM, new_location);
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

  new_room.setNumberClues(0);
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(0);
  new_room.setMyItems(new_items);

  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(2);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[new_grid_size_x * (
          new_grid_size_x / 2)].getMyLocation();
      new_exit_location.x -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(3, new_exit_location), 0, LOUNGE, 1, false);
    }
    else if (i == 1)
    {
      Point2D new_exit_location = new_room.getMyBackground()[new_grid_size_x *
             new_grid_size_y - (new_grid_size_x / 2)].getMyLocation();
      new_exit_location.y += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(2, new_exit_location), 0, GARDEN, 0, false);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[DORMS] = new_room;
}

/**
*   @brief   Setup Room Six
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomSix()
{
  Room new_room;
  GameObject* new_background = nullptr;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle;
  Exit* new_exits = nullptr;
  int new_grid_size_x = 8;
  int new_grid_size_y = 24;

  new_room.setRoomID(GARDEN);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_background = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                       (GRID_SIZE*
                                        (static_cast<float>(new_grid_size_x)*
                                         0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                      (GRID_SIZE*
                                       (static_cast<float>(new_grid_size_y)*
                                        0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {
    if(i == 105)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_background[i] = GameObject(2, new_location);
      left_side += GRID_SIZE;
    }
    else if(((i % new_grid_size_x == 1 || i % new_grid_size_x == 6) &&
        i > new_grid_size_x * 3 && i < new_grid_size_x * 22 ) ||
       i % new_grid_size_x == 3 || i % new_grid_size_x == 4 ||
       i == new_grid_size_x * (new_grid_size_y / 2) ||
       (i > new_grid_size_x * 2 && i < new_grid_size_x * 3 - 1 )||
       (i > new_grid_size_x * 8 && i < new_grid_size_x * 9 - 1 )||
       (i > new_grid_size_x * 16 && i < new_grid_size_x * 17 - 1 )||
       (i > new_grid_size_x * 22 && i < new_grid_size_x * 23 - 1 ))
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_background[i] = GameObject(0, new_location);
      left_side += GRID_SIZE;
    }
    else
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_background[i] = GameObject(1, new_location);
      left_side += GRID_SIZE;
    }

    if (i % new_grid_size_x == new_grid_size_x - 1)
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
    if (i == new_grid_size_x * 3|| i == new_grid_size_x * 3  + 2||
        i == new_grid_size_x * 3 + 5 || i == new_grid_size_x * 3  + 7 ||
        i == new_grid_size_x * 13|| i == new_grid_size_x * 17  + 2||
        i == new_grid_size_x * 17 + 5 || i == new_grid_size_x * 13  + 7 ||
        i == new_grid_size_x * 9  + 2 || i == new_grid_size_x * 9 + 5 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(FLOWER_TOP, new_location);
    }
    else if (i == new_grid_size_x * 5|| i == new_grid_size_x * 5  + 2 ||
             i == new_grid_size_x * 5 + 5 || i == new_grid_size_x * 5  + 7 ||
             i == new_grid_size_x * 7 || i == new_grid_size_x * 7  + 7 ||
             i == new_grid_size_x * 9 || i == new_grid_size_x * 9  + 7 ||
        i == new_grid_size_x * 19|| i == new_grid_size_x * 19  + 2 ||
        i == new_grid_size_x * 19 + 5 || i == new_grid_size_x * 19  + 7 ||
      i == new_grid_size_x * 10  + 2 || i == new_grid_size_x * 10 + 5 ||
    i == new_grid_size_x * 12  + 2 || i == new_grid_size_x * 12 + 5  ||
             i == new_grid_size_x * 14  + 2 || i == new_grid_size_x * 14 + 5||
      i == new_grid_size_x * 14   || i == new_grid_size_x * 14 + 7  ||
      i == new_grid_size_x * 16   || i == new_grid_size_x * 16 + 7   )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(FLOWER_MID_ONE, new_location);
    }
    else if (i == new_grid_size_x * 4 || i == new_grid_size_x * 4  + 2 ||
             i == new_grid_size_x * 6 || i == new_grid_size_x * 6  + 2 ||
             i == new_grid_size_x * 4 + 5 || i == new_grid_size_x * 4  + 7 ||
             i == new_grid_size_x * 6 + 5 || i == new_grid_size_x * 6  + 7 ||
             i == new_grid_size_x * 8 || i == new_grid_size_x * 8  + 7 ||
             i == new_grid_size_x * 10 || i == new_grid_size_x * 10  + 7 ||
             i == new_grid_size_x * 18 || i == new_grid_size_x * 18  + 2 ||
             i == new_grid_size_x * 20 || i == new_grid_size_x * 20  + 2 ||
             i == new_grid_size_x * 18 + 5 || i == new_grid_size_x * 18  + 7 ||
             i == new_grid_size_x * 20 + 5 || i == new_grid_size_x * 20  + 7 ||
             i == new_grid_size_x * 11  + 2 || i == new_grid_size_x * 11 + 5 ||
             i == new_grid_size_x * 13  + 2 || i == new_grid_size_x * 13 + 5 ||
             i == new_grid_size_x * 15   || i == new_grid_size_x * 15 + 7  ||
             i == new_grid_size_x * 17   || i == new_grid_size_x * 17 + 7  )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(FLOWER_MID_TWO, new_location);
    }
    else if (i == new_grid_size_x * 11 || i == new_grid_size_x * 7  + 2 ||
             i == new_grid_size_x * 7 + 5 || i == new_grid_size_x * 11  + 7 ||
        i == new_grid_size_x * 21 || i == new_grid_size_x * 21  + 2 ||
        i == new_grid_size_x * 21 + 5 || i == new_grid_size_x * 21  + 7||
             i == new_grid_size_x * 15  + 2 || i == new_grid_size_x * 15 + 5  )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(FLOWER_BOTTOM, new_location);
    }
    else if (i == 103)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(LAB_COAT, new_location);
    }
    else if ((i >= 0 && i < 3) || (i >= 5 && i < 8)
        || i == 113)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(VENDING_MACHINE, new_location);
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
  new_room.setupWalls();

  new_room.setNumberClues(0);
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(2);
  new_items = new Item[new_room.getNumberItems()];
  for (int i = 0; i < new_room.getNumberItems(); i++)
  {
    if (i == 0)
    {
      GameObject new_gameobject = new_background[103];
      Point2D new_location;
      new_location = new_gameobject.getMyLocation();
      new_items[i] = Item(GameObject(FUSE, new_location), 1);

    }
    else if (i == 1)
    {
      GameObject new_gameobject = new_background[2];
      Point2D new_location;
      new_location = new_gameobject.getMyLocation();
      new_items[i] = Item(GameObject(CAN, new_location), 4);

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
      new_linked_exits[0] = 1;
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
  new_puzzle.setNumberMovables(1);
  new_movable_gameobjects = new GameObject[new_puzzle.getNumberMovables()];
  Point2D* new_target_movable_locations = nullptr;
  new_target_movable_locations = new Point2D[new_puzzle.getNumberMovables()];
  for (int i = 0; i < new_puzzle.getNumberMovables(); i++)
  {
    if (i == 0)
    {
      Point2D new_location = new_background[97].getMyLocation();
      Point2D new_target_location = new_background[105].getMyLocation();
      new_movable_gameobjects[i] = GameObject(0, new_location);
      new_target_movable_locations[i].x = new_target_location.x;
      new_target_movable_locations[i].y = new_target_location.y;
    }
  }
  new_puzzle.setMyMovables(new_movable_gameobjects);
  new_puzzle.setTargetMovableLocations(new_target_movable_locations);

  std::string new_puzzle_solved_message = "You moved the crate out of the way!";
  new_puzzle.setPuzzleSolvedMessage(new_puzzle_solved_message);

  new_puzzle.setPuzzleID(1);
  new_puzzle.setRequiredItemID(-1);
  new_puzzle.setRequiredClueID(-1);
  new_puzzle.setPowerRequired(false);

  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(2);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_background[(
          new_grid_size_x / 2)].getMyLocation();
      new_exit_location.y -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(0, new_exit_location), 0, DORMS, 1, false);
    }
    if (i == 1)
    {
      Point2D new_exit_location = new_background[new_grid_size_x * (
          new_grid_size_y / 2)].getMyLocation();
      new_exit_location.x -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(3, new_exit_location), 1, GYM, 0, true);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[GARDEN] = new_room;
}

/**
*   @brief   Setup Room Seven
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomSeven()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle = Puzzle();
  Exit* new_exits = nullptr;
  int new_grid_size_x = 10;
  int new_grid_size_y = 8;

  new_room.setRoomID(GYM);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                 (GRID_SIZE*
                                  (static_cast<float>(new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                (GRID_SIZE*
                                 (static_cast<float>(new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {
    if (i >= 3  && i <= 6 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(TREADMILL_TOP, new_location);
    }
    else if (i >= new_grid_size_x + 3  && i <= new_grid_size_x + 6 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(TREADMILL_BOTTOM, new_location);
    }
    else if (i == 0  || i == 9 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(WEIGHTBENCH_TOP, new_location);
    }
    else if (i == new_grid_size_x  || i == new_grid_size_x + 9 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(WEIGHTBENCH_BOTTOM, new_location);
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

  new_room.setNumberClues(1);
  new_clues = new Clue[new_room.getNumberClues()];
  for (int i = 0; i < new_room.getNumberClues(); i++)
  {
    GameObject new_gameobject = new_room.getMyBackground()[13];
    new_gameobject.setMySpriteId(1);
    new_clues[i] = Clue(new_gameobject, 2);
  }
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(0);
  new_room.setMyItems(new_items);

  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(3);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[(new_grid_size_x*(
          new_grid_size_y / 2) + new_grid_size_x - 1)].getMyLocation();
      new_exit_location.x += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(1, new_exit_location), 0, GARDEN, 1, false);
    }
    else if (i == 1)
    {
      Point2D new_exit_location = new_room.getMyBackground()[(new_grid_size_x*(
          new_grid_size_y / 2) )]
          .getMyLocation();
      new_exit_location.x -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(3, new_exit_location), 1, LOCKERS, 0, false);
    }
    else if (i == 2)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x*new_grid_size_y) - (new_grid_size_x / 2 )]
          .getMyLocation();
      new_exit_location.y += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(2, new_exit_location), 2, CORRIDOR, 0, false);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[6] = new_room;
}

/**
*   @brief   Setup Room Eight
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomEight()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle = Puzzle();
  Exit* new_exits = nullptr;
  int new_grid_size_x = 10;
  int new_grid_size_y = 5;

  new_room.setRoomID(LOCKERS);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                 (GRID_SIZE*
                                  (static_cast<float>(new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                (GRID_SIZE*
                                 (static_cast<float>(new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {
    if (i >= 0  && i < new_grid_size_x )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(LOCKER_TOP, new_location);
    }
    else if (i >= new_grid_size_x * (new_grid_size_y - 1) &&
             i < new_grid_size_x * new_grid_size_y)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(LOCKER_BOTTOM, new_location);
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

  new_room.setNumberClues(1);
  new_clues = new Clue[new_room.getNumberClues()];
  for (int i = 0; i < new_room.getNumberClues(); i++)
  {
    GameObject new_gameobject = new_room.getMyBackground()[
        new_grid_size_x * (new_grid_size_y - 1) + 3];
    new_gameobject.setMySpriteId(1);
    new_clues[i] = Clue(new_gameobject, 3);
  }
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(0);
  new_room.setMyItems(new_items);

  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(2);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[(new_grid_size_x*(
          new_grid_size_y / 2) + new_grid_size_x - 1)].getMyLocation();
      new_exit_location.x += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(1, new_exit_location), 0, GYM, 1, false);
    }
    else if (i == 1)
    {
      Point2D new_exit_location = new_room.getMyBackground()[(new_grid_size_x*(
          new_grid_size_y / 2) )]
          .getMyLocation();
      new_exit_location.x -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(3, new_exit_location), 1, TOILETS_M, 0, false);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[LOCKERS] = new_room;
}

/**
*   @brief   Setup Room Nine
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomNine()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle = Puzzle();
  Exit* new_exits = nullptr;
  int new_grid_size_x = 10;
  int new_grid_size_y = 5;

  new_room.setRoomID(TOILETS_M);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                       (GRID_SIZE*
                                        (static_cast<float>(new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                      (GRID_SIZE*
                                       (static_cast<float>(new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {
    if (i >= 2  && i < new_grid_size_x - 2 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SHOWER, new_location);
    }
    else if (i % new_grid_size_x == 0 && (i != new_grid_size_x  || i != 0))
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(TOILET_LEFT, new_location);
    }
    else if ((i % new_grid_size_x == new_grid_size_x - 1 && (i != 29)))
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(BATHROOM_SINK_RIGHT, new_location);
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

  new_room.setNumberClues(0);
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(1);
  new_items = new Item[new_room.getNumberItems()];
  for (int i = 0; i < new_room.getNumberItems(); i++)
  {
    if (i == 0)
    {
      GameObject new_gameobject = new_room.getMyBackground()[6];
      Point2D new_location;
      new_location = new_gameobject.getMyLocation();
      new_items[i] = Item(GameObject(KEYCARD_GREEN, new_location), 11);

    }
  }
  new_room.setMyItems(new_items);

  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(2);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[(new_grid_size_x*(
          new_grid_size_y / 2) + new_grid_size_x - 1)].getMyLocation();
      new_exit_location.x += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(1, new_exit_location), 0, LOCKERS, 1, false);
    }
    else if (i == 1)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x*new_grid_size_y) - (new_grid_size_x / 2 ) - 1]
          .getMyLocation();
      new_exit_location.y += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(2, new_exit_location), 1, LIBRARY, 0, false);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[TOILETS_M] = new_room;
}

/**
*   @brief   Setup Room One
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomTen()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle = Puzzle();
  Exit* new_exits = nullptr;
  int new_grid_size_x = 10;
  int new_grid_size_y = 5;

  new_room.setRoomID(TOILETS_F);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                       (GRID_SIZE*
                                        (static_cast<float>(new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                      (GRID_SIZE*
                                       (static_cast<float>(new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {
    if (i >= 2  && i < new_grid_size_x - 2 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SHOWER, new_location);
    }
    else if (i % new_grid_size_x == 0 && (i != new_grid_size_x  || i != 0))
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(TOILET_LEFT, new_location);
    }
    else if (i % new_grid_size_x == new_grid_size_x - 1)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(BATHROOM_SINK_RIGHT, new_location);
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

  new_room.setNumberClues(1);
  new_clues = new Clue[new_room.getNumberClues()];
  for (int i = 0; i < new_room.getNumberClues(); i++)
  {
    GameObject new_gameobject = new_room.getMyBackground()[29];
    new_gameobject.setMySpriteId(1);
    new_clues[i] = Clue(new_gameobject, 4);
  }
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(1);
  new_items = new Item[new_room.getNumberItems()];
  for (int i = 0; i < new_room.getNumberItems(); i++)
  {
    if (i == 0)
    {
      GameObject new_gameobject = new_room.getMyBackground()[6];
      Point2D new_location;
      new_location = new_gameobject.getMyLocation();
      new_items[i] = Item(GameObject(KEYCARD_YELLOW, new_location), 2);
    }
  }
  new_room.setMyItems(new_items);

  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(1);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x*new_grid_size_y) - (new_grid_size_x / 2 ) - 1]
          .getMyLocation();
      new_exit_location.y += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(2, new_exit_location),
                          0, WASTE_DISPOSAL, 0, false);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[TOILETS_F] = new_room;
}

/**
*   @brief   Setup Room One
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomEleven()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle;
  Exit* new_exits = nullptr;
  int new_grid_size_x = 10;
  int new_grid_size_y = 10;

  new_room.setRoomID(WASTE_DISPOSAL);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                       (GRID_SIZE*
                                        (static_cast<float>(new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                      (GRID_SIZE*
                                       (static_cast<float>(new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {
    if ((i >= 10  && i <15) || (i >= 16  && i <20) || (i >= 32  && i <38)||
        (i >= 40  && i <48)||
        (i >= 70  && i <78))
    {
        Point2D new_location;
        new_location.x = left_side;
        new_location.y = top_side;
        new_foreground[i] = GameObject(WASTE_BARREL, new_location);
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

  new_room.setNumberClues(0);
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(0);
  new_room.setMyItems(new_items);

  new_puzzle.setNumberLinkedExits(1);
  int* new_linked_exits = nullptr;
  new_linked_exits = new int[new_puzzle.getNumberLinkedExits()];
  for (int i = 0; i < new_puzzle.getNumberLinkedExits(); i++)
  {
    if (i == 0)
    {
      new_linked_exits[0] = 2;
    }
  }
  new_puzzle.setLinkedExits(new_linked_exits);

  Switch* new_switches = nullptr;
  bool* new_target_switch_states = nullptr;
  new_puzzle.setNumberSwitches(1);
  new_switches = new Switch[new_puzzle.getNumberSwitches()];
  new_target_switch_states = new bool[new_puzzle.getNumberSwitches()];
  for (int i = 0; i < new_puzzle.getNumberSwitches(); i++)
  {
    if (i == 0)
    {
      Point2D new_location = new_room.getMyBackground()[30].getMyLocation();
      new_switches[i] = Switch(GameObject(0, new_location),
                               GameObject(0, new_location),
                               false);
      new_target_switch_states[i] = true;
    }
  }
  new_puzzle.setMySwitches(new_switches);
  new_puzzle.setTargetSwitchStates(new_target_switch_states);

  GameObject* new_movable_gameobjects = nullptr;
  new_puzzle.setNumberMovables(1);
  new_movable_gameobjects = new GameObject[new_puzzle.getNumberMovables()];
  Point2D* new_target_movable_locations = nullptr;
  new_target_movable_locations = new Point2D[new_puzzle.getNumberMovables()];
  for (int i = 0; i < new_puzzle.getNumberMovables(); i++)
  {
    if (i == 0)
    {
      Point2D new_location = new_room.getMyBackground()[24].getMyLocation();
      Point2D new_target_location = new_room.getMyBackground()[20].getMyLocation();
      new_movable_gameobjects[i] = GameObject(0, new_location);
      new_target_movable_locations[i].x = new_target_location.x;
      new_target_movable_locations[i].y = new_target_location.y;
    }
  }
  new_puzzle.setMyMovables(new_movable_gameobjects);
  new_puzzle.setTargetMovableLocations(new_target_movable_locations);

  std::string new_puzzle_solved_message = "You escape through the waste "
                                          "disposal chute!";
  new_puzzle.setPuzzleSolvedMessage(new_puzzle_solved_message);

  new_puzzle.setPuzzleID(3);
  new_puzzle.setRequiredItemID(11);
  new_puzzle.setRequiredClueID(-1);
  new_puzzle.setPowerRequired(true);
  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(3);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x / 2)].getMyLocation();
      new_exit_location.y -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(0, new_exit_location),
                          0, TOILETS_F, 0, false);
    }
    else if (i == 1)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x * (new_grid_size_y / 2) - 1)].getMyLocation();
      new_exit_location.x += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(1, new_exit_location),
                          1, LIBRARY, 1, false);
    }
    else if (i == 2)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x * (new_grid_size_y / 2))].getMyLocation();
      new_exit_location.x -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(3, new_exit_location),
                          2, EXIT, 1, true);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[WASTE_DISPOSAL] = new_room;
}

/**
*   @brief   Setup Room One
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomTwelve()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle;
  Exit* new_exits = nullptr;
  int new_grid_size_x = 10;
  int new_grid_size_y = 9;

  new_room.setRoomID(LIBRARY);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                       (GRID_SIZE*
                                        (static_cast<float>(new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                      (GRID_SIZE*
                                       (static_cast<float>(new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {
    if (i == 0  || i == 2  || i == 6 || i == 8 ||
        i == 80  || i == 82  || i == 84 || i == 86 || i == 88 )
    {
        Point2D new_location;
        new_location.x = left_side;
        new_location.y = top_side;
        new_foreground[i] = GameObject(BOOKSHELF_LEFT, new_location);
    }
    else if (i == 1  || i == 3 || i == 7 || i == 9 ||
                        i == 81  || i == 83  || i == 85 || i == 87 || i == 89 )
    {
        Point2D new_location;
        new_location.x = left_side;
        new_location.y = top_side;
        new_foreground[i] = GameObject(BOOKSHELF_RIGHT, new_location);
    }
    else if (i == 33  || i == 35)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(CHAIR_TOP, new_location);
    }
    else if (i == 43)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(TABLE_LEFT, new_location);
    }
    else if (i == 44  || i == 45)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(TABLE_CENTRE, new_location);
    }
    else if (i == 46)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(TABLE_RIGHT, new_location);
    }
    else if (i == 54  || i == 56)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(CHAIR_BOTTOM, new_location);
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

  new_room.setNumberClues(1);
  new_clues = new Clue[new_room.getNumberClues()];
  for (int i = 0; i < new_room.getNumberClues(); i++)
  {
    GameObject new_gameobject = new_room.getMyBackground()[45];
    new_gameobject.setMySpriteId(1);
    new_clues[i] = Clue(new_gameobject, 5);
  }
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(0);
  new_room.setMyItems(new_items);

  new_puzzle.setNumberLinkedExits(1);
  int* new_linked_exits = nullptr;
  new_linked_exits = new int[new_puzzle.getNumberLinkedExits()];
  new_linked_exits[0] = 1;
  new_puzzle.setLinkedExits(new_linked_exits);

  Switch* new_switches = nullptr;
  bool* new_target_switch_states = nullptr;
  new_puzzle.setNumberSwitches(0);
  new_puzzle.setMySwitches(new_switches);
  new_puzzle.setTargetSwitchStates(new_target_switch_states);

  GameObject* new_movable_gameobjects = nullptr;
  new_puzzle.setNumberMovables(0);
  Point2D* new_target_movable_locations = nullptr;
  new_puzzle.setMyMovables(new_movable_gameobjects);
  new_puzzle.setTargetMovableLocations(new_target_movable_locations);

  std::string new_puzzle_solved_message = "You open the door"
                                          " using the green keycard";
  new_puzzle.setPuzzleSolvedMessage(new_puzzle_solved_message);

  new_puzzle.setPuzzleID(6);
  new_puzzle.setRequiredItemID(11);
  new_puzzle.setRequiredClueID(-1);
  new_puzzle.setPowerRequired(true);
  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(3);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x / 2)].getMyLocation();
      new_exit_location.y -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(0, new_exit_location),
                          0, TOILETS_M, 1, false);
    }
    else if (i == 1)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x * (new_grid_size_y / 2))].getMyLocation();
      new_exit_location.x -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(3, new_exit_location),
                          1, WASTE_DISPOSAL, 1, true);
    }
    else if (i == 2)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x * (new_grid_size_y / 2) +
           new_grid_size_x - 1)].getMyLocation();
      new_exit_location.x += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(1, new_exit_location),
                          2, SUPPLY_ROOM, 0, false);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[LIBRARY] = new_room;
}

/**
*   @brief   Setup Room Thirteen
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomThirteen()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle;
  Exit* new_exits = nullptr;
  int new_grid_size_x = 12;
  int new_grid_size_y = 11;

  new_room.setRoomID(SUPPLY_ROOM);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                       (GRID_SIZE*
                                        (static_cast<float>(new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                      (GRID_SIZE*
                                       (static_cast<float>(new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {
    if ((i >= 13  && i < 23 ) || (i >= 72  && i < 80 ) || i == 50 || i == 38 ||
        i == 25 || i == 37 || (i >= 40  && i < 44 ) || i == 34 ||i == 81||
        (i >= 55  && i < 60 )|| i == 62  || i == 52 || i == 69|| i == 106||
        (i >= 93  && i < 95 )|| (i >= 109  && i < 119 ) || i == 87|| i == 97||
        i == 91 || i == 101|| i == 105)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(STORAGE_CRATE, new_location);
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

  new_room.setNumberClues(0);
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(0);
  new_room.setMyItems(new_items);

  new_puzzle.setNumberLinkedExits(0);
  int* new_linked_exits = nullptr;
  new_puzzle.setLinkedExits(new_linked_exits);

  Switch* new_switches = nullptr;
  bool* new_target_switch_states = nullptr;
  new_puzzle.setNumberSwitches(0);
  new_puzzle.setMySwitches(new_switches);
  new_puzzle.setTargetSwitchStates(new_target_switch_states);

  GameObject* new_movable_gameobjects = nullptr;
  new_puzzle.setNumberMovables(1);
  new_movable_gameobjects = new GameObject[new_puzzle.getNumberMovables()];
  Point2D* new_target_movable_locations = nullptr;
  new_target_movable_locations = new Point2D[new_puzzle.getNumberMovables()];
  for (int i = 0; i < new_puzzle.getNumberMovables(); i++)
  {
    if (i == 0)
    {
      Point2D new_location = new_room.getMyBackground()[29].getMyLocation();
      Point2D new_target_location = new_room.getMyBackground()[25].getMyLocation();
      new_movable_gameobjects[i] = GameObject(0, new_location);
      new_target_movable_locations[i].x = new_target_location.x;
      new_target_movable_locations[i].y = new_target_location.y;
    }
  }
  new_puzzle.setMyMovables(new_movable_gameobjects);
  new_puzzle.setTargetMovableLocations(new_target_movable_locations);

  std::string new_puzzle_solved_message;
  new_puzzle.setPuzzleSolvedMessage(new_puzzle_solved_message);

  new_puzzle.setPuzzleID(-1);
  new_puzzle.setRequiredItemID(-1);
  new_puzzle.setRequiredClueID(-1);
  new_puzzle.setPowerRequired(false);
  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(2);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x * (new_grid_size_y / 2))].getMyLocation();
      new_exit_location.x -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(3, new_exit_location),
                          0, LIBRARY, 2, false);
    }
    else if (i == 1)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x * (new_grid_size_y / 2) +
           new_grid_size_x - 1)].getMyLocation();
      new_exit_location.x += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(1, new_exit_location),
                          1, CORRIDOR, 1, false);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[SUPPLY_ROOM] = new_room;
}

/**
*   @brief   Setup Room Fourteen
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomFourteen()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle;
  Exit* new_exits = nullptr;
  int new_grid_size_x = 8;
  int new_grid_size_y = 20;

  new_room.setRoomID(CORRIDOR);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                       (GRID_SIZE*
                                        (static_cast<float>(
                                            new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                      (GRID_SIZE*
                                       (static_cast<float>(
                                           new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {

      new_foreground[i].setMySpriteId(-1);
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

  new_room.setNumberClues(0);
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(0);
  new_room.setMyItems(new_items);

  new_puzzle.setNumberLinkedExits(2);
  int* new_linked_exits = nullptr;
  new_linked_exits = new int[new_puzzle.getNumberLinkedExits()];
  for (int i = 0; i < new_puzzle.getNumberLinkedExits(); i++)
  {
    if (i == 0)
    {
      new_linked_exits[i] = 3;
    }
    else if (i == 1)
    {
      new_linked_exits[i] = 4;
    }
  }
  new_puzzle.setLinkedExits(new_linked_exits);

  Switch* new_switches = nullptr;
  bool* new_target_switch_states = nullptr;
  new_puzzle.setNumberSwitches(0);
  new_puzzle.setMySwitches(new_switches);
  new_puzzle.setTargetSwitchStates(new_target_switch_states);

  GameObject* new_movable_gameobjects = nullptr;
  new_puzzle.setNumberMovables(0);
  Point2D* new_target_movable_locations = nullptr;
  new_puzzle.setMyMovables(new_movable_gameobjects);
  new_puzzle.setTargetMovableLocations(new_target_movable_locations);

  std::string new_puzzle_solved_message = "You open the door"
                                          " using the yellow keycard";
  new_puzzle.setPuzzleSolvedMessage(new_puzzle_solved_message);

  new_puzzle.setPuzzleID(5);
  new_puzzle.setRequiredItemID(2);
  new_puzzle.setRequiredClueID(-1);
  new_puzzle.setPowerRequired(true);
  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(6);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x  / 2)].getMyLocation();
      new_exit_location.y -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(0, new_exit_location),
                          0, GYM, 2, false);
    }
    else if (i == 1)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x * (new_grid_size_y / 4))].getMyLocation();
      new_exit_location.x -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(3, new_exit_location),
                          1, SUPPLY_ROOM, 1, false);
    }
    else if (i == 2)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x * (new_grid_size_y / 2) +
              (new_grid_size_x * 2) )].getMyLocation();
      new_exit_location.x -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(3, new_exit_location),
                          2, OBSERVATION, 0, false);
    }
    else if (i == 3)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x * (new_grid_size_y / 4) +
           new_grid_size_x - 1)].getMyLocation();
      new_exit_location.x += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(1, new_exit_location),
                          3, LAB_ONE, 0, true);
    }
    else if (i == 4)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x * (new_grid_size_y / 2) +
           (new_grid_size_x * 3) - 1)].getMyLocation();
      new_exit_location.x += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(1, new_exit_location),
                          4, LAB_TWO, 0, true);
    }
    else if (i == 5)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x * new_grid_size_y) -
              (new_grid_size_x / 2)].getMyLocation();
      new_exit_location.y += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(2, new_exit_location),
                          5, LEAD_TECH_OFFICE, 0, false);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[CORRIDOR] = new_room;
}

/**
*   @brief   Setup Room Fifteen
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomFifteen()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle = Puzzle();
  Exit* new_exits = nullptr;
  int new_grid_size_x = 16;
  int new_grid_size_y = 9;

  new_room.setRoomID(LAB_ONE);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x * new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                       (GRID_SIZE*
                                        (static_cast<float>(
                                             new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                      (GRID_SIZE*
                                       (static_cast<float>(
                                            new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {
    if (i == 0|| i == 6 || i == 12)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SYNTH_TOP_LEFT, new_location);
    }
    else if (i == 1|| i == 7|| i == 13)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SYNTH_TOP_RIGHT, new_location);
    }
    else if (i == 2|| i == 8|| i == 14)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SYNTH_TERMINAL, new_location);
    }
    else if (i == 3|| i == 9|| i == 15)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SURGEONS_TOOLS, new_location);
    }
    else if (i == new_grid_size_x|| i == new_grid_size_x + 6||
             i == new_grid_size_x + 12)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SYNTH_BOTTOM_LEFT, new_location);
    }
    else if (i == new_grid_size_x + 1|| i == new_grid_size_x + 7||
             i == new_grid_size_x + 13)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SYNTH_BOTTOM_RIGHT, new_location);
    }
    else if (i == new_grid_size_x * 6 + 2 || i == new_grid_size_x * 6  + 7 ||
             i == new_grid_size_x * 6  + 12)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(POOL_TOP_LEFT, new_location);
    }
    else if (i == new_grid_size_x  * 6 + 3 || i == new_grid_size_x * 6  + 8 ||
             i == new_grid_size_x  * 6 + 13)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(POOL_TOP_RIGHT, new_location);
    }
    else if (i == new_grid_size_x * 7 + 2 || i == new_grid_size_x * 7 + 7 ||
             i == new_grid_size_x * 7 + 12)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(POOL_BOTTOM_LEFT, new_location);
    }
    else if (i == new_grid_size_x * 7  + 3 || i == new_grid_size_x * 7 + 8 ||
             i == new_grid_size_x  * 7 + 13)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(POOL_BOTTOM_RIGHT, new_location);
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

  new_room.setNumberClues(1);
  new_clues = new Clue[new_room.getNumberClues()];
  for (int i = 0; i < new_room.getNumberClues(); i++)
  {
    GameObject new_gameobject = new_room.getMyBackground()[8];
    new_gameobject.setMySpriteId(1);
    new_clues[i] = Clue(new_gameobject, 6);
  }
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(0);
  new_room.setMyItems(new_items);

  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(1);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x *(new_grid_size_y / 2))].getMyLocation();
      new_exit_location.x -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(3, new_exit_location),
                          0, CORRIDOR, 3, false);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[LAB_ONE] = new_room;
}

/**
*   @brief   Setup Room One
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomSixteen()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle = Puzzle();
  Exit* new_exits = nullptr;
  int new_grid_size_x = 16;
  int new_grid_size_y = 7;

  new_room.setRoomID(LAB_TWO);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                       (GRID_SIZE*
                                        (static_cast<float>(
                                             new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                      (GRID_SIZE*
                                       (static_cast<float>(
                                            new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {

    if (i == 0|| i == 6 || i == 12)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(COMPUTERS_TOP_LEFT, new_location);
    }
    else if (i == 1|| i == 7|| i == 13)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(COMPUTERS_TOP_CENTRE, new_location);
    }
    else if (i == 2|| i == 8|| i == 14)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(COMPUTERS_TOP_RIGHT, new_location);
    }
    else if (i == 3|| i == 9|| i == 15)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SYNTH_BRAIN, new_location);
    }
    else if (i == new_grid_size_x|| i == new_grid_size_x + 6||
             i == new_grid_size_x + 12)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(COMPUTERS_LEFT_MIDDLE, new_location);
    }
    else if (i == new_grid_size_x + 2|| i == new_grid_size_x + 8||
             i == new_grid_size_x + 14)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(COMPUTERS_RIGHT_MIDDLE, new_location);
    }
    else if (i == new_grid_size_x * 2 || i == new_grid_size_x * 2 + 6||
             i == new_grid_size_x * 2 + 12)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(COMPUTERS_LEFT_BOTTOM, new_location);
    }
    else if (i == new_grid_size_x * 2 + 2|| i == new_grid_size_x * 2 + 8||
             i == new_grid_size_x * 2 + 14)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(COMPUTERS_RIGHT_BOTTOM, new_location);
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

  new_room.setNumberClues(1);
  new_clues = new Clue[new_room.getNumberClues()];
  for (int i = 0; i < new_room.getNumberClues(); i++)
  {
    GameObject new_gameobject = new_room.getMyBackground()[13];
    new_gameobject.setMySpriteId(1);
    new_clues[i] = Clue(new_gameobject, 7);
  }
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(1);
  new_items = new Item[new_room.getNumberItems()];
  for (int i = 0; i < new_room.getNumberItems(); i++)
  {
    if (i == 0)
    {
      GameObject new_gameobject = new_room.getMyBackground()[44];
      Point2D new_location;
      new_location = new_gameobject.getMyLocation();
      new_items[i] = Item(GameObject(KEYCARD_BLUE, new_location), 3);
    }
  }
  new_room.setMyItems(new_items);

  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(1);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x   *(new_grid_size_y / 2))].getMyLocation();
      new_exit_location.x -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(3, new_exit_location),
                          0, CORRIDOR, 4, false);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[LAB_TWO] = new_room;
}

/**
*   @brief   Setup Room Seventeen
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomSeventeen()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle = Puzzle();
  Exit* new_exits = nullptr;
  int new_grid_size_x = 10;
  int new_grid_size_y = 7;

  new_room.setRoomID(OBSERVATION);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                       (GRID_SIZE*
                                        (static_cast<float>(
                                             new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                      (GRID_SIZE*
                                       (static_cast<float>(
                                            new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {

    if (i ==  24 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(DESK_LEFT, new_location);
    }
    else if (i ==  25 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(DESK_RIGHT, new_location);
    }
    else if (i ==  34 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(DESK_CHAIR_BOTTOM, new_location);
    }
    else if (i >=  0 && i < new_grid_size_x)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(COMPUTERS_TOP_CENTRE, new_location);
    }
    else if (i ==  67 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(CAFE_TABLE_LEFT, new_location);
    }
    else if (i ==  68 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(CAFE_TABLE_RIGHT, new_location);
    }
    else if (i ==  57 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(CHAIR_TOP, new_location);
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

  new_room.setNumberClues(0);
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(0);
  new_room.setMyItems(new_items);

  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(2);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x   *(new_grid_size_y / 2)+
           new_grid_size_x - 1)].getMyLocation();
      new_exit_location.x += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(1, new_exit_location),
                          0, CORRIDOR, 2, false);
    }
    else if (i == 1)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x   *(new_grid_size_y / 2) )].getMyLocation();
      new_exit_location.x -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(3, new_exit_location),
                          1, TESTING, 0, false);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[OBSERVATION] = new_room;
}

/**
*   @brief   Setup Room Eighteen
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomEighteen()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle;
  Exit* new_exits = nullptr;
  int new_grid_size_x = 20;
  int new_grid_size_y = 20;

  new_room.setRoomID(TESTING);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                       (GRID_SIZE*
                                        (static_cast<float>(
                                             new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                      (GRID_SIZE*
                                       (static_cast<float>(
                                            new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {
    if ((i >= new_grid_size_x + 1 && i < new_grid_size_x  + 8) ||
        (i >= new_grid_size_x + 9 && i < new_grid_size_x  * 2) ||
        (i >= new_grid_size_x * 3 + 1 && i < new_grid_size_x * 3  + 19) ||
        (i >= new_grid_size_x * 5 && i < new_grid_size_x * 5  + 7) ||
        (i >= new_grid_size_x * 5 + 8 && i < new_grid_size_x * 5  + 9) ||
        (i >= new_grid_size_x * 5 + 10 && i < new_grid_size_x * 5  + 20) ||
        (i >= new_grid_size_x * 7 && i < new_grid_size_x * 7  + 3) ||
        (i >= new_grid_size_x * 7 + 4 && i < new_grid_size_x * 7  + 12) ||
        (i >= new_grid_size_x * 7 + 13 && i < new_grid_size_x * 7  + 17) ||
        (i >= new_grid_size_x * 7 + 18 && i < new_grid_size_x * 7  + 20) ||
        (i >= new_grid_size_x * 9 && i < new_grid_size_x * 9  + 2) ||
        (i >= new_grid_size_x * 9 + 4 && i < new_grid_size_x * 9  + 9) ||
        (i >= new_grid_size_x * 9 + 11 && i < new_grid_size_x * 9  + 15) ||
        (i >= new_grid_size_x * 9 + 16 && i < new_grid_size_x * 9  + 20) ||
        (i >= new_grid_size_x * 11 && i < new_grid_size_x * 11  + 6) ||
        (i >= new_grid_size_x * 11 + 7 && i < new_grid_size_x * 11  + 17) ||
        (i >= new_grid_size_x * 11 + 18 && i < new_grid_size_x * 11  + 20) ||
        (i >= new_grid_size_x * 13  && i < new_grid_size_x * 13  + 12) ||
        (i >= new_grid_size_x * 13 + 13 && i < new_grid_size_x * 13  + 16) ||
        (i >= new_grid_size_x * 13 + 17 && i < new_grid_size_x * 13  + 20) ||
        (i >= new_grid_size_x * 15  && i < new_grid_size_x * 15  + 6) ||
        (i >= new_grid_size_x * 15 + 7 && i < new_grid_size_x * 15  + 10) ||
        (i >= new_grid_size_x * 15 + 11 && i < new_grid_size_x * 15  + 19) ||
        (i >= new_grid_size_x * 16  && i < new_grid_size_x * 16  + 6) ||
        (i >= new_grid_size_x * 16 + 7 && i < new_grid_size_x * 16  + 10) ||
        (i >= new_grid_size_x * 17 + 7 && i < new_grid_size_x * 17  + 10) ||
        (i >= new_grid_size_x * 16 + 11 && i < new_grid_size_x * 16  + 13) ||
        (i >= new_grid_size_x * 18 + 1 && i < new_grid_size_x * 18  + 16)  ||
        (i >= new_grid_size_x * 18 + 17 && i < new_grid_size_x * 18  + 20) ||
        i == new_grid_size_x * 2 + 1 ||  i == new_grid_size_x * 4 + 8 ||
        i == new_grid_size_x * 6 + 2 ||  i == new_grid_size_x * 6 + 8 ||
        i == new_grid_size_x * 8 + 2 ||  i == new_grid_size_x * 8 + 11 ||
        i == new_grid_size_x * 10 + 5 ||  i == new_grid_size_x * 10 + 16 ||
        i == new_grid_size_x * 12 + 4 ||  i == new_grid_size_x * 12 + 15||
        i == new_grid_size_x * 14 + 5 ||  i == new_grid_size_x * 14 + 15)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(WASTE_BARREL_TWO, new_location);
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

  new_room.setNumberClues(0);
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(0);
  new_room.setMyItems(new_items);

  new_puzzle.setNumberLinkedExits(0);
  int* new_linked_exits = nullptr;
  new_puzzle.setLinkedExits(new_linked_exits);

  Switch* new_switches = nullptr;
  bool* new_target_switch_states = nullptr;
  new_puzzle.setNumberSwitches(0);
  new_puzzle.setMySwitches(new_switches);
  new_puzzle.setTargetSwitchStates(new_target_switch_states);

  GameObject* new_movable_gameobjects = nullptr;
  new_puzzle.setNumberMovables(5);
  new_movable_gameobjects = new GameObject[new_puzzle.getNumberMovables()];
  Point2D* new_target_movable_locations = nullptr;
  new_target_movable_locations = new Point2D[new_puzzle.getNumberMovables()];
  for (int i = 0; i < new_puzzle.getNumberMovables(); i++)
  {
    if (i == 0)
    {
      Point2D new_location = new_room.getMyBackground()[168].getMyLocation();
      Point2D new_target_location = new_room.getMyBackground()[25].getMyLocation();
      new_movable_gameobjects[i] = GameObject(0, new_location);
      new_target_movable_locations[i].x = new_target_location.x;
      new_target_movable_locations[i].y = new_target_location.y;
    }
    else if (i == 1)
    {
      Point2D new_location = new_room.getMyBackground()[310].getMyLocation();
      Point2D new_target_location = new_room.getMyBackground()[27].getMyLocation();
      new_movable_gameobjects[i] = GameObject(0, new_location);
      new_target_movable_locations[i].x = new_target_location.x;
      new_target_movable_locations[i].y = new_target_location.y;
    }
    else if (i == 2)
    {
      Point2D new_location = new_room.getMyBackground()[319].getMyLocation();
      Point2D new_target_location = new_room.getMyBackground()[27].getMyLocation();
      new_movable_gameobjects[i] = GameObject(0, new_location);
      new_target_movable_locations[i].x = new_target_location.x;
      new_target_movable_locations[i].y = new_target_location.y;
    }
    else if (i == 3)
    {
      Point2D new_location = new_room.getMyBackground()[338].getMyLocation();
      Point2D new_target_location = new_room.getMyBackground()[27].getMyLocation();
      new_movable_gameobjects[i] = GameObject(0, new_location);
      new_target_movable_locations[i].x = new_target_location.x;
      new_target_movable_locations[i].y = new_target_location.y;
    }
    else if (i == 4)
    {
      Point2D new_location = new_room.getMyBackground()[157].getMyLocation();
      Point2D new_target_location = new_room.getMyBackground()[27].getMyLocation();
      new_movable_gameobjects[i] = GameObject(0, new_location);
      new_target_movable_locations[i].x = new_target_location.x;
      new_target_movable_locations[i].y = new_target_location.y;
    }
  }
  new_puzzle.setMyMovables(new_movable_gameobjects);
  new_puzzle.setTargetMovableLocations(new_target_movable_locations);

  std::string new_puzzle_solved_message;
  new_puzzle.setPuzzleSolvedMessage(new_puzzle_solved_message);

  new_puzzle.setPuzzleID(-1);
  new_puzzle.setRequiredItemID(2);
  new_puzzle.setRequiredClueID(-1);
  new_puzzle.setPowerRequired(true);
  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(2);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x   *(new_grid_size_y / 2)+
           new_grid_size_x - 1)].getMyLocation();
      new_exit_location.x += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(1, new_exit_location),
                          0, OBSERVATION, 1, false);
    }
    else if (i == 1)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x   *(new_grid_size_y / 2) )].getMyLocation();
      new_exit_location.x -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(3, new_exit_location),
                          1, SERVERS, 0, false);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[TESTING] = new_room;
}

/**
*   @brief   Setup Room Nineteen
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomNineteen()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle = Puzzle();
  Exit* new_exits = nullptr;
  int new_grid_size_x = 12;
  int new_grid_size_y = 11;

  new_room.setRoomID(SERVERS);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                       (GRID_SIZE*
                                        (static_cast<float>(
                                             new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                      (GRID_SIZE*
                                       (static_cast<float>(
                                            new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {
    if (i % new_grid_size_x ==  0 ||
        (i % new_grid_size_x ==  3  && i < new_grid_size_x * 5)||
        (i % new_grid_size_x ==  3  && i > new_grid_size_x * 6)||
        (i % new_grid_size_x ==  6  && i < new_grid_size_x * 5)||
        (i % new_grid_size_x ==  6  && i > new_grid_size_x * 6)||
        (i % new_grid_size_x ==  9  && i < new_grid_size_x * 5)||
        (i % new_grid_size_x ==  9  && i > new_grid_size_x * 6))
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SERVER_LEFT, new_location);
    }
    else if  ((i % new_grid_size_x ==  2  && i < new_grid_size_x * 5) ||
        (i % new_grid_size_x ==  2  && i > new_grid_size_x * 6)||
        (i % new_grid_size_x ==  5  && i < new_grid_size_x * 5)||
        (i % new_grid_size_x ==  5  && i > new_grid_size_x * 6)||
        (i % new_grid_size_x ==  8  && i < new_grid_size_x * 5)||
        (i % new_grid_size_x ==  8  && i > new_grid_size_x * 6)||
        (i % new_grid_size_x ==  11  && i < new_grid_size_x * 5)||
        (i % new_grid_size_x ==  11  && i > new_grid_size_x * 6))
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SERVER_RIGHT, new_location);
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

  new_room.setNumberClues(0);
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(1);
  new_items = new Item[new_room.getNumberItems()];
  for (int i = 0; i < new_room.getNumberItems(); i++)
  {
    if (i == 0)
    {
      GameObject new_gameobject = new_room.getMyBackground()[0];
      Point2D new_location;
      new_location = new_gameobject.getMyLocation();
      new_items[i] = Item(GameObject(KEYCARD_RED, new_location), 10);

    }
  }
  new_room.setMyItems(new_items);

  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(1);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x   *(new_grid_size_y / 2)+
           new_grid_size_x - 1)].getMyLocation();
      new_exit_location.x += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(1, new_exit_location),
                          0, TESTING, 1, false);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[SERVERS] = new_room;
}

/**
*   @brief   Setup Room Twenty
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomTwenty()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle;
  Exit* new_exits = nullptr;
  int new_grid_size_x = 12;
  int new_grid_size_y = 9;

  new_room.setRoomID(REACTOR);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                       (GRID_SIZE*
                                        (static_cast<float>(
                                             new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                      (GRID_SIZE*
                                       (static_cast<float>(
                                            new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {

    if (i == 0 || i == new_grid_size_x * 3 || i == new_grid_size_x * 6)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(REACTOR_TOP_LEFT, new_location);
    }
    else if (i == 1 || i == new_grid_size_x * 3 + 1 || i == new_grid_size_x * 6 + 1)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(REACTOR_TOP_RIGHT, new_location);
    }
    else if (i ==  new_grid_size_x || i ==  new_grid_size_x * 4 ||
             i ==  new_grid_size_x * 7)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(REACTOR_MIDDLE_LEFT, new_location);
    }
    else if (i ==  new_grid_size_x + 1 || i ==  new_grid_size_x * 4 + 1 ||
             i ==  new_grid_size_x * 7 + 1)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(REACTOR_MIDDLE_RIGHT, new_location);
    }
    else if (i ==  new_grid_size_x * 2 || i ==  new_grid_size_x * 5 ||
             i ==  new_grid_size_x * 8)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(REACTOR_BOTTOM_LEFT, new_location);
    }
    else if (i ==  new_grid_size_x * 2 + 1 || i ==  new_grid_size_x * 5 + 1 ||
             i ==  new_grid_size_x * 8 + 1)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(REACTOR_BOTTOM_RIGHT, new_location);
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

  new_room.setNumberClues(0);
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(0);
  new_room.setMyItems(new_items);

  new_puzzle.setNumberLinkedExits(0);
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
  new_puzzle.setNumberSwitches(5);
  new_switches = new Switch[new_puzzle.getNumberSwitches()];
  new_target_switch_states = new bool[new_puzzle.getNumberSwitches()];
  for (int i = 0; i < new_puzzle.getNumberSwitches(); i++)
  {
    if (i == 0)
    {
      Point2D new_location = new_room.getMyBackground()[2].getMyLocation();
      new_switches[i] = Switch(GameObject(0, new_location),
                               GameObject(0, new_location),
                               false);
      new_target_switch_states[i] = true;
    }
    else if (i == 1)
    {
      Point2D new_location = new_room.getMyBackground()[
          new_grid_size_x * (new_grid_size_y - 7) + 2].getMyLocation();
      new_switches[i] = Switch(GameObject(0, new_location),
                               GameObject(0, new_location),
                               true);
      new_target_switch_states[i] = false;
    }
    else if (i == 2)
    {
      Point2D new_location = new_room.getMyBackground()[
          new_grid_size_x * (new_grid_size_y - 5) + 2].getMyLocation();
      new_switches[i] = Switch(GameObject(0, new_location),
                               GameObject(0, new_location),
                               true);
      new_target_switch_states[i] = true;
    }
    else if (i == 3)
    {
      Point2D new_location = new_room.getMyBackground()[
          new_grid_size_x * (new_grid_size_y - 3) + 2].getMyLocation();
      new_switches[i] = Switch(GameObject(0, new_location),
                               GameObject(0, new_location),
                               false);
      new_target_switch_states[i] = false;
    }
    else if (i == 4)
    {
      Point2D new_location = new_room.getMyBackground()[
          new_grid_size_x * (new_grid_size_y - 1) + 2].getMyLocation();
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
  Point2D* new_target_movable_locations = nullptr;
  new_puzzle.setMyMovables(new_movable_gameobjects);
  new_puzzle.setTargetMovableLocations(new_target_movable_locations);

  std::string new_puzzle_solved_message = "You have restored power to the "
                                          "facility.";
  new_puzzle.setPuzzleSolvedMessage(new_puzzle_solved_message);

  new_puzzle.setPuzzleID(4);
  new_puzzle.setRequiredItemID(1);
  new_puzzle.setRequiredClueID(-1);
  new_puzzle.setPowerRequired(false);

  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(1);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x   *(new_grid_size_y / 2)+
           new_grid_size_x - 1)].getMyLocation();
      new_exit_location.x += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(1, new_exit_location),
                          0, WORKSHOP, 0, false);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[REACTOR] = new_room;
}

/**
*   @brief   Setup Room TwentyOne
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomTwentyOne()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle;
  Exit* new_exits = nullptr;
  int new_grid_size_x = 10;
  int new_grid_size_y = 5;

  new_room.setRoomID(WORKSHOP);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                       (GRID_SIZE*
                                        (static_cast<float>(
                                             new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                      (GRID_SIZE*
                                       (static_cast<float>(
                                            new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {
    if (i ==  new_grid_size_x * 2 + 7 || i ==  new_grid_size_x * 2 + 2 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(TABLE_TOP, new_location);
    }
    else if (i ==  new_grid_size_x * 3 + 7 || i ==  new_grid_size_x * 3 + 2)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(TABLE_BOTTOM, new_location);
    }
    else if (i ==  new_grid_size_x  + 2  || i ==  new_grid_size_x * 4 + 4)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(DESK_LEFT, new_location);
    }
    else if (i ==  new_grid_size_x  + 3 || i ==  new_grid_size_x * 4 + 5)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(DESK_RIGHT, new_location);
    }
    else if (i ==  new_grid_size_x  + 7 || i ==  new_grid_size_x + 5 ||
             i ==  new_grid_size_x * 3 + 5)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(STORAGE_CRATE, new_location);
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

  new_room.setNumberClues(1);
  new_clues = new Clue[new_room.getNumberClues()];
  for (int i = 0; i < new_room.getNumberClues(); i++)
  {
    GameObject new_gameobject = new_room.getMyBackground()[new_grid_size_x  + 12];
    new_gameobject.setMySpriteId(1);
    new_clues[i] = Clue(new_gameobject, 10);
  }
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(3);
  new_items = new Item[new_room.getNumberItems()];
  for (int i = 0; i < new_room.getNumberItems(); i++)
  {
    if (i == 0)
    {
      GameObject new_gameobject = new_room.getMyBackground()[new_grid_size_x* 3 + 7 ];
      Point2D new_location;
      new_location = new_gameobject.getMyLocation();
      new_items[i] = Item(GameObject(HAMMER, new_location), 8);

    }
    else if (i == 1)
    {
      GameObject new_gameobject = new_room.getMyBackground()[new_grid_size_x  + 3];
      Point2D new_location;
      new_location = new_gameobject.getMyLocation();
      new_items[i] = Item(GameObject(PLIERS, new_location), 9);

    }
    else if (i == 2)
    {
      GameObject new_gameobject = new_room.getMyBackground()[new_grid_size_x * 3 + 5];
      Point2D new_location;
      new_location = new_gameobject.getMyLocation();
      new_items[i] = Item(GameObject(MAGNIFIER, new_location), 12);

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
  new_puzzle.setMySwitches(new_switches);
  new_puzzle.setTargetSwitchStates(new_target_switch_states);

  GameObject* new_movable_gameobjects = nullptr;
  new_puzzle.setNumberMovables(2);
  new_movable_gameobjects = new GameObject[new_puzzle.getNumberMovables()];
  Point2D* new_target_movable_locations = nullptr;
  new_target_movable_locations = new Point2D[new_puzzle.getNumberMovables()];
  for (int i = 0; i < new_puzzle.getNumberMovables(); i++)
  {
    if (i == 0)
    {
      Point2D new_location = new_room.getMyBackground()[7].getMyLocation();
      Point2D new_target_location = new_room.getMyBackground()[25].getMyLocation();
      new_movable_gameobjects[i] = GameObject(0, new_location);
      new_target_movable_locations[i].x = new_target_location.x;
      new_target_movable_locations[i].y = new_target_location.y;
    }
    else if (i == 1)
    {
      Point2D new_location = new_room.getMyBackground()[47].getMyLocation();
      Point2D new_target_location = new_room.getMyBackground()[27].getMyLocation();
      new_movable_gameobjects[i] = GameObject(0, new_location);
      new_target_movable_locations[i].x = new_target_location.x;
      new_target_movable_locations[i].y = new_target_location.y;
    }
  }
  new_puzzle.setMyMovables(new_movable_gameobjects);
  new_puzzle.setTargetMovableLocations(new_target_movable_locations);

  std::string new_puzzle_solved_message = "You use the key to unlock "
                                          "the door.";
  new_puzzle.setPuzzleSolvedMessage(new_puzzle_solved_message);

  new_puzzle.setPuzzleID(7);
  new_puzzle.setRequiredItemID(7);
  new_puzzle.setRequiredClueID(-1);
  new_puzzle.setPowerRequired(false);
  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(2);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          new_grid_size_x   *(new_grid_size_y / 2)].getMyLocation();
      new_exit_location.x -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(3, new_exit_location),
                          0, REACTOR, 0, true);
    }
    else if (i == 1)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x   *(new_grid_size_y / 2)+
           new_grid_size_x - 1)].getMyLocation();
      new_exit_location.x += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(1, new_exit_location),
                          1, INFIRMARY, 0, false);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[WORKSHOP] = new_room;
}

/**
*   @brief   Setup Room TwentyTwo
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomTwentyTwo()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle = Puzzle();
  Exit* new_exits = nullptr;
  int new_grid_size_x = 12;
  int new_grid_size_y = 9;

  new_room.setRoomID(INFIRMARY);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                       (GRID_SIZE*
                                        (static_cast<float>(
                                             new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                      (GRID_SIZE*
                                       (static_cast<float>(
                                            new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {
    if (i == 1|| i == 4 || i == 7 || i == 10 ||
        i == new_grid_size_x  * 7 + 1 || i == new_grid_size_x * 7  + 4 ||
        i == new_grid_size_x  * 7 + 7 || i == new_grid_size_x * 7  + 10 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(BED_TOP, new_location);
    }
    else if (i == new_grid_size_x + 1|| i == new_grid_size_x + 4||
             i == new_grid_size_x + 7 || i == new_grid_size_x + 10 ||
             i == new_grid_size_x  * 8 + 1 || i == new_grid_size_x * 8  + 4 ||
             i == new_grid_size_x  * 8 + 7 || i == new_grid_size_x * 8  + 10 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(BED_BOTTOM, new_location);
    }
    else if (i == 2|| i == 5 || i == 8 || i == 11 ||
             i == new_grid_size_x * 8 + 2 || i == new_grid_size_x * 8  + 5 ||
             i == new_grid_size_x * 8  + 8 || i == new_grid_size_x * 8  + 11 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SURGEONS_TOOLS, new_location);
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

  new_room.setNumberClues(0);
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(0);
  new_room.setMyItems(new_items);

  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(2);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          new_grid_size_x   *(new_grid_size_y / 2)].getMyLocation();
      new_exit_location.x -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(3, new_exit_location),
                          0, WORKSHOP, 1, false);
    }
    else if (i == 1)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x   *(new_grid_size_y / 2)+
           new_grid_size_x - 1)].getMyLocation();
      new_exit_location.x += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(1, new_exit_location),
                          1, LEAD_TECH_OFFICE, 1, false);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[INFIRMARY] = new_room;
}

/**
*   @brief   Setup Room TwentyThree
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomTwentyThree()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle = Puzzle();
  Exit* new_exits = nullptr;
  int new_grid_size_x = 12;
  int new_grid_size_y = 9;

  new_room.setRoomID(LEAD_TECH_OFFICE);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                       (GRID_SIZE*
                                        (static_cast<float>(
                                             new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                      (GRID_SIZE*
                                       (static_cast<float>(
                                            new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {
    if (i ==  10 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(DESK_LEFT, new_location);
    }
    else if (i ==  11 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(DESK_RIGHT, new_location);
    }
    else if (i ==  23 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(DESK_CHAIR_BOTTOM, new_location);
    }
    else if (i ==  0 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SAFE, new_location);
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

  new_room.setNumberClues(1);
  new_clues = new Clue[new_room.getNumberClues()];
  for (int i = 0; i < new_room.getNumberClues(); i++)
  {
    GameObject new_gameobject = new_room.getMyBackground()[10];
    new_gameobject.setMySpriteId(1);
    new_clues[i] = Clue(new_gameobject, 8);
  }
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(1);
  new_items = new Item[new_room.getNumberItems()];
  for (int i = 0; i < new_room.getNumberItems(); i++)
  {
    if (i == 0)
    {
      GameObject new_gameobject = new_room.getMyBackground()[0];
      Point2D new_location;
      new_location = new_gameobject.getMyLocation();
      new_items[i] = Item(GameObject(KEY, new_location), 7);

    }
  }
  new_room.setMyItems(new_items);

  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(3);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x / 2)].getMyLocation();
      new_exit_location.y -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(0, new_exit_location),
                          0, CORRIDOR, 5, false);
    }
    else if (i == 1)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          new_grid_size_x   *(new_grid_size_y / 2)].getMyLocation();
      new_exit_location.x -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(3, new_exit_location),
                          1, INFIRMARY, 1, false);
    }
    else if (i == 2)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x   *(new_grid_size_y / 2)+
           new_grid_size_x - 1)].getMyLocation();
      new_exit_location.x += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(1, new_exit_location),
                          2, SECURITY, 0, false);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[LEAD_TECH_OFFICE] = new_room;
}

/**
*   @brief   Setup Room TwentyFour
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomTwentyFour()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle = Puzzle();
  Exit* new_exits = nullptr;
  int new_grid_size_x = 10;
  int new_grid_size_y = 7;

  new_room.setRoomID(SECURITY);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                       (GRID_SIZE*
                                        (static_cast<float>(
                                             new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                      (GRID_SIZE*
                                       (static_cast<float>(
                                            new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {

    if (i ==  24 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(DESK_LEFT, new_location);
    }
    else if (i ==  25 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(DESK_RIGHT, new_location);
    }
    else if (i ==  34 )
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(DESK_CHAIR_BOTTOM, new_location);
    }
    else if (i >=  0 && i < new_grid_size_x)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(COMPUTERS_TOP_CENTRE, new_location);
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

  new_room.setNumberClues(1);
  new_clues = new Clue[new_room.getNumberClues()];
  for (int i = 0; i < new_room.getNumberClues(); i++)
  {
    GameObject new_gameobject = new_room.getMyBackground()[24];
    new_gameobject.setMySpriteId(1);
    new_clues[i] = Clue(new_gameobject, 9);
  }
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(0);
  new_room.setMyItems(new_items);

  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(2);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          new_grid_size_x   *(new_grid_size_y / 2)].getMyLocation();
      new_exit_location.x -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(3, new_exit_location),
                          0, LEAD_TECH_OFFICE, 2, false);
    }
    else if (i == 1)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x   * new_grid_size_y
            - (new_grid_size_x/ 2))].getMyLocation();
      new_exit_location.y += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(2, new_exit_location),
                          1, RECEPTION, 0, false);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[SECURITY] = new_room;
}

/**
*   @brief   Setup Room TwentyFive
*   @details This is a temporary function is used to setup a room.
*   @param   none
*   @return  void
*/
void MyGame::setupRoomTwentyFive()
{
  Room new_room;
  GameObject* new_foreground = nullptr;
  Clue* new_clues = nullptr;
  Item* new_items = nullptr;
  Puzzle new_puzzle;
  Exit* new_exits = nullptr;
  int new_grid_size_x = 10;
  int new_grid_size_y = 9;

  new_room.setRoomID(RECEPTION);
  new_room.setMyGridsizeX(new_grid_size_x);
  new_room.setMyGridsizeY(new_grid_size_y);

  new_room.setupFloorStandard();
  new_room.setupWalls();

  new_foreground = new GameObject[(new_grid_size_x*new_grid_size_y)];
  auto left_side = static_cast<float>(GAME_WIDTH*0.5-
                                       (GRID_SIZE*
                                        (static_cast<float>(
                                             new_grid_size_x)*0.5f)));
  auto top_side = static_cast<float>(GAME_HEIGHT*0.5-
                                      (GRID_SIZE*
                                       (static_cast<float>(
                                            new_grid_size_y)*0.5f)));
  for (int i = 0; i < (new_grid_size_x*new_grid_size_y); i++)
  {

    if (i ==  23 || i ==  25)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(DESK_LEFT, new_location);
    }
    else if (i ==  24 || i ==  26)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(DESK_RIGHT, new_location);
    }
    else if (i ==  13)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(CHAIR_TOP, new_location);
    }
    else if (i ==  0 || i == 20|| i == 40|| i == 60)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SOFA_LEFT_TOP, new_location);
    }
    else if (i ==  10 || i == 30|| i == 50|| i == 70)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SOFA_LEFT_BOTTOM, new_location);
    }
    else if (i ==  9 || i == 29|| i == 49|| i == 69)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SOFA_RIGHT_TOP, new_location);
    }
    else if (i ==  19 || i == 39|| i == 59|| i == 79)
    {
      Point2D new_location;
      new_location.x = left_side;
      new_location.y = top_side;
      new_foreground[i] = GameObject(SOFA_RIGHT_BOTTOM, new_location);
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

  new_room.setNumberClues(0);
  new_room.setMyClues(new_clues);

  new_room.setNumberItems(0);
  new_room.setMyItems(new_items);

  new_puzzle.setNumberLinkedExits(1);
  int* new_linked_exits = nullptr;
  new_linked_exits = new int[new_puzzle.getNumberLinkedExits()];
  for (int i = 0; i < new_puzzle.getNumberLinkedExits(); i++)
  {
    if (i == 0)
    {
      new_linked_exits[0] = 1;
    }
  }
  new_puzzle.setLinkedExits(new_linked_exits);

  Switch* new_switches = nullptr;
  bool* new_target_switch_states = nullptr;
  new_puzzle.setNumberSwitches(0);
  new_puzzle.setMySwitches(new_switches);
  new_puzzle.setTargetSwitchStates(new_target_switch_states);

  GameObject* new_movable_gameobjects = nullptr;
  new_puzzle.setNumberMovables(0);
  Point2D* new_target_movable_locations = nullptr;
  new_puzzle.setMyMovables(new_movable_gameobjects);
  new_puzzle.setTargetMovableLocations(new_target_movable_locations);

  std::string new_puzzle_solved_message = "You use the blue keycard to unlock "
                                          "the door.";
  new_puzzle.setPuzzleSolvedMessage(new_puzzle_solved_message);

  new_puzzle.setPuzzleID(8);
  new_puzzle.setRequiredItemID(3);
  new_puzzle.setRequiredClueID(-1);
  new_puzzle.setPowerRequired(false);
  new_room.setMyPuzzle(new_puzzle);

  new_room.setNumberExits(2);
  new_exits = new Exit[new_room.getNumberExits()];
  for (int i = 0; i < new_room.getNumberExits(); i++)
  {
    if (i == 0)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          new_grid_size_x / 2].getMyLocation();
      new_exit_location.y -= (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(0, new_exit_location),
                          0, SECURITY, 1, false);
    }
    else if (i == 1)
    {
      Point2D new_exit_location = new_room.getMyBackground()[
          (new_grid_size_x   * new_grid_size_y
           - (new_grid_size_x/ 2))].getMyLocation();
      new_exit_location.y += (GRID_SIZE / 2);
      new_exits[i] = Exit(GameObject(2, new_exit_location),
                          1, EXIT, 2, true);
    }
  }
  new_room.setMyExits(new_exits);
  visited_rooms[RECEPTION] = new_room;
}


