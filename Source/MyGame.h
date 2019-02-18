//
// Created by Huxy on 03/10/2018.
//

#ifndef HELLOASGE_MYGAME_H
#define HELLOASGE_MYGAME_H

#include "Constants.h"
#include "Room.h"
#include "soloud.h"
#include "soloud_speech.h"
#include "soloud_thread.h"
#include "soloud_wav.h"
#include <Engine/OGLGame.h>

class MyGame : public ASGE::OGLGame
{
 public:
  ~MyGame() override = default;

  bool init() override;

  void update(const ASGE::GameTime& game_time) override;

  void render(const ASGE::GameTime& game_time) override;

 private:
  void setupGame();
  void setupRoomOne();
  void setupRoomTwo();
  void setupRoomThree();
  void setupRoomFour();
  void setupRoomFive();
  void setupRoomSix();
  void setupRoomSeven();
  void setupRoomEight();
  void setupRoomNine();
  void setupRoomTen();
  void setupRoomEleven();
  void setupRoomTwelve();
  void setupRoomThirteen();
  void setupRoomFourteen();
  void setupRoomFifteen();
  void setupRoomSixteen();
  void setupRoomSeventeen();
  void setupRoomEighteen();
  void setupRoomNineteen();
  void setupRoomTwenty();
  void setupRoomTwentyOne();
  void setupRoomTwentyTwo();
  void setupRoomTwentyThree();
  void setupRoomTwentyFour();
  void setupRoomTwentyFive();
  void setupFloorSprites();
  void setupWallSprites();
  void setupForegroundSprites();
  void setupClueSprites();
  void setupSwitchSprites();
  void setupExitSprites();
  void setupItemSprites();
  void setupMovableSprites();
  void setupPlayerSprites();

  void keyHandler(ASGE::SharedEventData data);
  void keyHandlerMainMenu(const ASGE::KeyEvent* key);
  void keyHandlerInGame(const ASGE::KeyEvent* key);
  void keyHandlerInventory(const ASGE::KeyEvent* key);
  void keyHandlerPauseMenu(const ASGE::KeyEvent* key);

  void changeRoom();

  void updateSplash(double dt_sec);
  void updateInGame(double dt_sec);

  void renderSplash();
  void renderMainMenu();
  void renderInGame();
  void renderTextDisplay();
  void renderPause();
  void renderGameOver();
  void renderInventory();
  void renderClues();
  void renderMap();

  void saveGame();
  void loadGame();

  int key_callback_id = -1; /**< Key Input Callback ID. */

  ASGE::Sprite* splash_screen = nullptr;
  ASGE::Sprite* main_menu = nullptr;
  ASGE::Sprite* main_menu_icon = nullptr;
  ASGE::Sprite* pause_menu = nullptr;
  ASGE::Sprite* game_screen = nullptr;
  ASGE::Sprite* text_box = nullptr;
  ASGE::Sprite* inventory_screen = nullptr;
  ASGE::Sprite* inventory_highlighter = nullptr;
  ASGE::Sprite* map = nullptr;

  ASGE::Sprite* floor_sprites[NUM_FLOOR_SPRITES];
  ASGE::Sprite* wall_sprites[NUM_WALL_SPRITES];
  ASGE::Sprite* foreground_sprites[NUM_FOREGROUND_SPRITES];
  ASGE::Sprite* clue_sprites[NUM_CLUE_SPRITES];
  ASGE::Sprite* switch_on_sprites[NUM_SWITCH_SPRITES];
  ASGE::Sprite* switch_off_sprites[NUM_SWITCH_SPRITES];
  ASGE::Sprite* movable_sprites[NUM_MOVABLE_SPRITES];
  ASGE::Sprite* exit_sprites[NUM_EXIT_SPRITES];
  ASGE::Sprite* item_sprites[NUM_ITEM_SPRITES];
  ASGE::Sprite* player_sprites[NUM_PLAYER_SPRITES];
  Player player_one;
  Room current_room;
  Room visited_rooms[NUM_ROOMS];

  double animation_counter;
  int game_state;
  int main_menu_option;
  int pause_menu_option;
  int inventory_menu_option;
  std::string text_to_display;
  bool power_on;
  bool change_room;
  int exit_check[3];
  float background_volume = 0.5f;

  SoLoud::Soloud soloud;        // SoLoud engine core
  SoLoud::Speech speech;        // A sound source (speech, in this case)
  SoLoud::Wav menu_click;       // A sound source (speech, in this case)
  SoLoud::Wav discovery;        // A sound source (speech, in this case)
  SoLoud::Wav footsteps[5];     // A sound source (speech, in this case)
  SoLoud::Wav background_music; // A sound source
  SoLoud::Wav page_open;
  SoLoud::Wav page_close;
  SoLoud::Wav lever;
  SoLoud::Wav background_music_1;
};

#endif // HELLOASGE_MYGAME_H
