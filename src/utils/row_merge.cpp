#pragma once

#include "row_merge.hpp"

namespace utils
{
vector<int> MergeRow(vector<int>& v)
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

vector<vector<int>> RotateMatrix(vector<vector<int>>& v)
{
  int n = v.size();
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < i; j++)
    {
      swap(v[i][j], v[j][i]);
    }
  }

  for (int i = 0; i < n; i++)
  {
    reverse(v[i].begin(), v[i].end());
  }
  return v;
}

}  // namespace utils
