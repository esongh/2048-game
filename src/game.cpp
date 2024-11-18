#pragma once
#include "game.hpp"

namespace game
{
board_2048::board_2048(int size)
  : size_(size)
  , gen_(std::random_device{}())  
{
  board_.resize(size * size);
  add_random_tile();
  add_random_tile();
}

void board_2048::move(int dir)
{
}

int board_2048::get_tile(int x, int y) const
{
  return board_[x * size_ + y];
}

void board_2048::add_random_tile()
{
  std::uniform_int_distribution<int> dist(0, size_ * size_ - 1);
  int pos = dist(gen_);
  while (board_[pos] != 0)
  {
    pos = dist(gen_);
  }
  std::uniform_int_distribution<int> dist2(0, 1);
  board_[pos] = dist2(gen_) ? 2 : 4;
}
}
