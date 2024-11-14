#pragma once

#include "row_merge.hpp"

namespace utils
{
std::vector<int> MergeRow(std::vector<int>& v)
{
  int size = v.size();
  for (int i = 0; i < size; i++)
  {
    if (v[i] == 0) continue;

    for (int j = i + 1; j < size; j++)
    {
      if (v[i] == v[j])
      {
        v[i] *= 2;
        v[j] = 0;
      }
    }
  }
  for (int i = 0; i < size; i++)
  {
    if (v[i] == 0)
    {
      for (int j = i + 1; j < size; j++)
      {
        if (v[j] != 0)
        {
          v[i] = v[j];
          v[j] = 0;
          break;
        }
      }
    }
  }

  for (int i = 0; i < size; i++)
  {
    if (v[i] == 0)
    {
      for (int j = i + 1; j < size; j++)
      {
        if (v[j] != 0)
        {
          v[i] = v[j];
          v[j] = 0;
          break;
        }
      }
    }
  }
  return v;
}
}  // namespace utils