#pragma once
#include "game.hpp"

#include "row_merge.hpp"
namespace game
{
board_2048::board_2048(int size)
  : size_(size)
  , gen_(std::random_device{}())  
{
  board_.resize(size * size);
  add_random_tile();
  add_random_tile();
  add_random_tile();
  add_random_tile();
}

void board_2048::move(Direction dir)
{
  auto dir_ = (4 - dir) % 4;
  auto reDir = dir % 4;
  for (; dir_ != 0; dir_--)
  {
    utils::RotateMatrixR(board_, size_);
  }
  
  for (int i = 0; i < size_; i++)
  {
    std::vector<int> row{board_.begin() + i * size_, board_.begin() + (i + 1) * size_};
    utils::MergeRow(row);
    std::copy(row.begin(), row.end(), board_.begin() + i * size_);
  }

  for (; reDir != 0; reDir--)
  {
    utils::RotateMatrixR(board_, size_);
  }
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
