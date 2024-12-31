#include <iostream>
#include <vector>
#include <format>

#include "row_merge.hpp"

void PrintTiles(core::animationTiles& tiles)
{
  for (int i = 0; i < tiles.preNum.size(); i++)
  {
    std::cout << i << " ";
  }
  std::cout << std::endl;
  std::cout << "================" << std::endl;
  for (int i = 0; i < tiles.preNum.size(); i++)
  {
    std::cout << tiles.preNum[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "================" << std::endl;
  
  for (int i = 0; i < tiles.slideDistance.size(); i++)
  {
    std::cout << tiles.slideDistance[i].from << " ";
  }
  std::cout << std::endl;
  std::cout << "================" << std::endl;

  for (int i = 0; i < tiles.slideDistance.size(); i++)
  {
    std::cout << tiles.slideDistance[i].step << " ";
  }
  std::cout << std::endl;
  std::cout << "================" << std::endl;

  for (int i = 0; i < tiles.tileNumber.size(); i++)
  {
    std::cout << tiles.tileNumber[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "================" << std::endl;
}

int main()
{
  core::animationTiles tiles;
  std::vector<int> row = {0, 2, 0, 2, 0, 0, 2, 2,0, 2};
  tiles = utils::MergeRowAnimated(row);
  std::cout << "After merge" << std::endl;
  PrintTiles(tiles);

  std::cout << "vector" << std::endl;
  for (auto i : row)
  {
    std::cout << i << " ";
  }

  return 0;
}
