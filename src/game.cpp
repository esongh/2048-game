#pragma once
#include "game.hpp"

#include "core/game_core.hpp"
#include "row_merge.hpp"
namespace game
{
board_2048::board_2048(int size) : size_(size), gen_(std::random_device{}())
{
  board_.resize(size * size);
  add_random_tile();
  add_random_tile();
}

void board_2048::move(core::Direction dir)
{
  if (dir == core::Direction::Unset)
  {
    return;
  }

  if (!try_move(dir))
  {
    return;
  }

  if (is_win())
  {
    return;
  }

  if (is_full())
  {
    return;
  }

  add_random_tile();
}

std::vector<core::animationTiles> board_2048::get_animationTiles() const { return animationTiles_; }

bool board_2048::is_valid_move(core::Direction dir) const { return true; }

int board_2048::get_tile(int x, int y) const { return board_[x * size_ + y]; }

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
  // board_[pos] = 2;
}

bool board_2048::is_win() const
{
  return std::find(board_.begin(), board_.end(), 2048) != board_.end();
}

bool board_2048::is_full() const
{
  return std::find(board_.begin(), board_.end(), 0) == board_.end();
}

bool board_2048::is_game_over() const
{
  if (is_full())
  {
    return false;
  }
  if (is_win())
  {
    return true;
  }
  auto Movable = [](const std::vector<int>& row)
  {
    for (int i = 0; i < row.size() - 1; i++)
    {
      if (row[i] == row[i + 1])
      {
        return true;
      }
    }
    return false;
  };

  for (int i = 0; i < size_; i++)
  {
    std::vector<int> row{board_.begin() + i * size_, board_.begin() + (i + 1) * size_};
    if (Movable(row))
    {
      return false;
    }
  }
  return true;
}

void board_2048::populateRowsCols()
{
  rows_.lines.clear();
  columns_.lines.clear();
  for (int i = 0; i < size_; i++)
  {
    std::vector<int> row{board_.begin() + i * size_, board_.begin() + (i + 1) * size_};
    rows_.lines.push_back(row);
  }

  for (int i = 0; i < size_; i++)
  {
    std::vector<int> col;
    for (int j = 0; j < size_; j++)
    {
      col.push_back(board_[j * size_ + i]);
    }
    columns_.lines.push_back(col);
  }
}

bool board_2048::try_move(core::Direction dir)
{
  if (dir == core::Direction::Unset)
  {
    return false;
  }

  auto dir_ = (4 - dir) % 4;
  auto reDir = dir % 4;
  std::vector<int> board = board_;
  for (; dir_ != 0; dir_--)
  {
    utils::RotateMatrixR(board, size_);
  }

  animationTiles_.clear();
  for (int i = 0; i < size_; i++)
  {
    std::vector<int> row{board.begin() + i * size_, board.begin() + (i + 1) * size_};
    core::animationTiles tiles = utils::MergeRowAnimated(row);
    animationTiles_.push_back(tiles);
    std::copy(row.begin(), row.end(), board.begin() + i * size_);
  }

  for (; reDir != 0; reDir--)
  {
    utils::RotateMatrixR(board, size_);
  }

  if (board_ == board)
  {
    animationTiles_.clear();
    return false;
  }

  board_.swap(board);
  return true;
}
}  // namespace game
