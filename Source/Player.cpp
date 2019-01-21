//
// Created by haydn on 20/01/2019.
//

#include "Player.h"

GameObject Player::getPlayerGameobject()
{
  return player_gameobject;
}

void Player::setPlayerGameobject(GameObject new_player_gameobject)
{
  player_gameobject = new_player_gameobject;
}

ASGE::Sprite* Player::getPlayerSprite(int index)
{
  return player_sprites[index];
}

int* Player::getInventory()
{
  return inventory;
}

int* Player::getCluesFound()
{
  return clues_found;
}

void Player::setCluesFound(int* new_clues_found)
{
  clues_found = new_clues_found;
}

int* Player::getPuzzlesSolved()
{
  return puzzles_solved;
}

void Player::setPuzzlesSolved(int* new_puzzles_solved)
{
  puzzles_solved = new_puzzles_solved;
}

int Player::getDirection()
{
  return direction;
}

void Player::setDirection(int new_direction)
{
  direction = new_direction;
}

bool Player::isMoving()
{
  return moving;
}

void Player::setMoving(bool new_moving)
{
  moving = new_moving;
}

int Player::getSpriteIndex()
{
  return sprite_index;
}

void Player::setSpriteIndex(int new_sprite_index)
{
  sprite_index = new_sprite_index;
}

int Player::getNumberCluesFound()
{
  return number_clues_found;
}

void Player::setNumberCluesFound(int new_number_clues_found)
{
  number_clues_found = new_number_clues_found;
}

int Player::getNumberPuzzlesSolved()
{
  return number_puzzles_solved;
}

void Player::setNumberPuzzlesSolved(int new_number_puzzles_solved)
{
  number_puzzles_solved = new_number_puzzles_solved;
}

void Player::setPlayerSprites(ASGE::Sprite* new_player_sprites[])
{
  for (int i = 0; i < 16; i++)
  {
    player_sprites[i] = new_player_sprites[i];
  }

}


