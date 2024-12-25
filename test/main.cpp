#include <iostream>
#include <vector>

#include "row_merge.hpp"

void PrintTiles(core::animationTiles& tiles)
{
  for (int i = 0; i < tiles.preNum.size(); i++)
  {
    std::cout << tiles.preNum[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "================" << std::endl;
  
  for (int i = 0; i < tiles.slideDistance.size(); i++)
  {
    std::cout << tiles.slideDistance[i] << " ";
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
  tiles.preNum = {0, 2, 0, 2, 0, 0, 2, 2,0, 2};
  PrintTiles(tiles);
  utils::MergeRow(tiles);
  std::cout << "After merge" << std::endl;
  PrintTiles(tiles);

  return 0;
}
