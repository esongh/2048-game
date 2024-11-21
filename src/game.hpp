#include <vector>
#include <random>

namespace game
{
enum Direction : uint8_t
{
  LEFT = 0,
  UP = 1,
  RIGHT = 2,
  DOWN = 3
};

class board_2048
{
public:
  explicit board_2048(int size = 4);

  void move(Direction dir);
  
  int get_tile(int x, int y) const;
private:
  std::vector<int> board_;
  int size_ = 4;
  
  std::default_random_engine gen_;
  
  void add_random_tile();
};
}  // namespace game
