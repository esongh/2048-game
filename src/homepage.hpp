#include "game.hpp"

#include "ftxui/dom/elements.hpp"

class homepage
{
 public:
  homepage();
	
	void startGame();
 private:
  ftxui::Element game_view();
	
	void move(core::Direction dir);
	game::board_2048 board_{3};
};
