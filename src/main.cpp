#include <iostream>
#include <vector>

#include "row_merge.hpp"

void PrintVec(std::vector<int> v)
{
  for (int i = 0; i < v.size(); i++)
  {
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
}

int main()
{
  std::vector<int> v = {0, 0, 2, 0, 4, 0, 0, 4};
  int size = v.size();
  std::cout << "Original vector: ";
  PrintVec(v);

  utils::MergeRow(v);

  std::cout << "Aligned vector: ";
  PrintVec(v);
  return 0;
}