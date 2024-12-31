#include <vector>

#include "game_core.hpp"
namespace utils
{
using namespace std;

void MergeRow(vector<int>& v);

void RotateMatrixR(vector<int>& v, int size);

core::animationTiles MergeRowAnimated(vector<int>& row);
}  // namespace utils
