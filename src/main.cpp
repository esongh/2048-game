#include <iostream>
#include <vector>

#include "row_merge.hpp"
#include "game.hpp"

void PrintVec(std::vector<int> v)
{
  for (int i = 0; i < v.size(); i++)
  {
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
}

void PrintMatrix(std::vector<std::vector<int>> v)
{
  for (int i = 0; i < v.size(); i++)
  {
    PrintVec(v[i]);
  }
}

int main()
{
  int brd_size = 4;
  game::board_2048 board(brd_size);

  auto print = [](game::board_2048 board, int brd_size) {
  for (int i = 0; i < brd_size; i++)
  {
    for (int j = 0; j < brd_size; j++)
    {
      std::cout << board.get_tile(i, j) << " ";
    }
    std::cout << std::endl;
  }
  };

  print(board, brd_size);
  std::cout << "Move left" << std::endl;
  board.move(game::Direction::UP);
  print(board, brd_size);

  return 0;
}
