#include <iostream>
#include <vector>

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

  for (int i = 0; i < size; i++)
  {
    if (v[i] == 0)
    {
      continue;
    }
    for (int j = i + 1; j < size; j++)
    {
      if (v[i] == v[j])
      {
        v[i] *= 2;
        v[j] = 0;
      }
    }
  }
  std::cout << "Merged vector: ";
  PrintVec(v);
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

  std::cout << "Aligned vector: ";
  PrintVec(v);
  return 0;
}