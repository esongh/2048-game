#pragma once

#include <stdint.h>
#include <vector>
#include <utility>

namespace core
{
enum Direction : int8_t
{
  Unset = -1,
  LEFT = 0,
  UP = 1,
  RIGHT = 2,
  DOWN = 3
};

struct motion
{
  int from;
  int step;
};

struct animationTiles
{
	std::vector<int> tileNumber;
	std::vector<int> preNum;
  std::vector<motion> slideDistance;
};
} // namespace core
