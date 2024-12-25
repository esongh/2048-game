#include <stdint.h>
#include <vector>

namespace core
{
enum Direction : uint8_t
{
  LEFT = 0,
  UP = 1,
  RIGHT = 2,
  DOWN = 3
};

struct animationTiles
{
	std::vector<int> tileNumber;
	std::vector<int> preNum;
	std::vector<int> slideDistance;
};

} // namespace core
