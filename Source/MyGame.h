//
// Created by Huxy on 03/10/2018.
//

#ifndef HELLOASGE_MYGAME_H
#define HELLOASGE_MYGAME_H

#include <Engine/OGLGame.h>
#include "Room.h"
#include "Constants.h"

class MyGame : public ASGE::OGLGame
{
 public:
  ~MyGame() override = default;

  bool init() override;
void setupGame();


  void update(const ASGE::GameTime& game_time) override;



  void render(const ASGE::GameTime& game_time) override;

 private:

  void keyHandler(const ASGE::SharedEventData data);
  void renderSplash();
  void renderMainMenu();
  void renderInGame();
  void renderTextDisplay();
  void renderPause();
  void renderGameOver();
  void renderInventory();


  void setupRooms();

void exitGame();
void loadGame();



  int  key_callback_id = -1;	        /**< Key Input Callback ID. */

  ASGE::Sprite* splash_screen = nullptr;
  ASGE::Sprite* main_menu = nullptr;
  ASGE::Sprite* main_menu_icon = nullptr;
  ASGE::Sprite* pause_menu = nullptr;
  ASGE::Sprite* game_screen = nullptr;
  ASGE::Sprite* text_box = nullptr;
  ASGE::Sprite* inventory_screen = nullptr;
  ASGE::Sprite* inventory_highlighter = nullptr;

Player player_one;
Room current_room;
Room* visited_rooms;

double animation_counter;
  int game_state;
  int main_menu_option;
  int pause_menu_option;
  int inventory_menu_option;
  std::string text_to_display;
};

#endif // HELLOASGE_MYGAME_H
