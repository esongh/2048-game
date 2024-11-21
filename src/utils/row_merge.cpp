#pragma once

#include "row_merge.hpp"

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
}  // namespace utils
