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

void PrintMatrix(std::vector<std::vector<int>> v)
{
  for (int i = 0; i < v.size(); i++)
  {
    PrintVec(v[i]);
  }
}

int main()
{
  using namespace std;
  vector<vector<int>> v = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

  cout << "Original matrix:" << endl;
  PrintMatrix(v);

  utils::RotateMatrix(v);

  cout << "Rotated matrix:" << endl;
  PrintMatrix(v);
  return 0;
}
