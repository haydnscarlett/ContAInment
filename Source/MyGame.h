//
// Created by Huxy on 03/10/2018.
//

#ifndef HELLOASGE_MYGAME_H
#define HELLOASGE_MYGAME_H

#include "Constants.h"
#include "Player.h"
#include <Engine/OGLGame.h>
class MyGame : public ASGE::OGLGame
{
 public:
  ~MyGame() override = default;

  bool init() override;
  void setupGame();
  void setupPlayer();

  void update(const ASGE::GameTime& game_time) override;

  void render(const ASGE::GameTime& game_time) override;

  private:
  void keyHandler(const ASGE::SharedEventData data);
  void renderSplash();
  void renderMainMenu();
  void renderInGame();
  void renderGameOver();
  void renderPause();
  void renderInventory();

  int key_callback_id = -1; /**< Key Input Callback ID. */

  ASGE::Sprite* splash_screen = nullptr;
  ASGE::Sprite* main_menu = nullptr;
  ASGE::Sprite* main_menu_icon = nullptr;

  Player player_one;

  double animation_counter;
  int game_state;
  int main_menu_option;
};

#endif // HELLOASGE_MYGAME_H
