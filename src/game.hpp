#include <random>
#include <vector>

#include "core/game_core.hpp"
namespace game
{
class board_2048
{
 public:
  explicit board_2048(int size = 4);

  void move(core::Direction dir);

  int get_tile(int x, int y) const;
  int get_size() const { return size_; }
  bool is_win() const;
  bool is_game_over() const;

  std::vector<core::animationTiles> get_animationTiles() const;

 private:
  struct Rows
  {
    std::vector<std::vector<int>> lines;
  };
  
  struct Columns
  {
    std::vector<std::vector<int>> lines;
  };

  std::vector<int> board_;
  int size_ = 4;
  std::vector<core::animationTiles> animationTiles_;

  std::default_random_engine gen_;
  
  Rows rows_;
  Columns columns_;

  void add_random_tile();
  bool is_full() const;

  bool is_valid_move(core::Direction dir) const;
  void populateRowsCols();
  bool try_move(core::Direction dir);
};
}  // namespace game
