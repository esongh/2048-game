#include "game_ui.hpp"

#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"

class homepage
{
 public:
  homepage();
	
	void startGame();
 private:
	game::board_2048 board_{4};
	Component gameUi;
};
