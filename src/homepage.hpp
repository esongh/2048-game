#include "game.hpp"

class homepage
{
 public:
  homepage();
	
	void startGame();
 private:
	game::board_2048 board_{3};
};
