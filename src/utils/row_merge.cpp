#pragma once

#include "row_merge.hpp"

using namespace core;

namespace 
{
std::vector<int> slideVec(const std::vector<int>& row)
{
  int ite = 0;
  std::vector<int> temp(row.size(), 0);
  for (const auto i : row)
  {
    if (i != 0)
    {
      temp[ite] = i;
      ite++;
    }
  }
  return temp;
}

void slideVec(animationTiles& tiles)
{
  int slideBase = 0;
  tiles.tileNumber.clear();
  tiles.slideDistance.clear();
  for (int i = 0; i < tiles.preNum.size(); i++)
  {
    if (tiles.preNum[i] == 0)
    {
      slideBase++;
    }
    else
    {
      tiles.tileNumber.push_back(tiles.preNum[i]);
      tiles.slideDistance.push_back({i, slideBase});
    }
  }
}

void mergeAndSlide(animationTiles& tiles)
{
  int slideBase = 0;
  std::vector<int> temp;
  for (int i = 0; i < tiles.tileNumber.size(); i++)
  {
    if (tiles.tileNumber[i] == 0)
    {
      continue;
    }
    tiles.slideDistance[i].step += slideBase;
    if (i + 1 < tiles.tileNumber.size() && tiles.tileNumber[i] == tiles.tileNumber[i + 1])
    {
      slideBase++;
      tiles.tileNumber[i] *= 2;
      tiles.tileNumber[i + 1] = 0;
      tiles.slideDistance[i + 1].step += slideBase;
    }
    temp.push_back(tiles.tileNumber[i]);
  }
  tiles.tileNumber = std::move(temp);
}
} // namespace 

namespace utils
{
void MergeRow(vector<int>& v)
{
  // slide, merge, and slide again
  int size = v.size();
  auto forMerge = slideVec(v);
  for (int i = 0; i < size; i++)
  {
    if (forMerge[i] == 0)
      continue;

    for (int j = i + 1; j < size; j++)
    {
      if (forMerge[i] == forMerge[j])
      {
        forMerge[i] *= 2;
        forMerge[j] = 0;
      }
      if (forMerge[j] != 0)
        break;
    }
  }
  
  v = slideVec(forMerge);
}

void RotateMatrixR(vector<int>& v, int size)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < i; j++)
    {
      swap(v[i * size + j], v[j * size + i]);
    }
  }
  
  for (int i = 0; i < size; i++)
  {
    reverse(v.begin() + i * size, v.begin() + (i + 1) * size);
  }
}

void MergeRow(core::animationTiles& tiles)
{
  slideVec(tiles);
  mergeAndSlide(tiles);
}
}  // namespace utils
