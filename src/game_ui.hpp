#include <chrono>
#include <ftxui/component/animation.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>

#include "game.hpp"

using namespace ftxui;

class GameUi : public ftxui::ComponentBase
{
 public:
  GameUi(game::board_2048& game) : gameCore(game) {}

  void OnAnimation(ftxui::animation::Params& params) override;

  ftxui::Element Render() override;

  bool OnEvent(Event e) override;

 private:
  ftxui::Box box_;
  bool started = false;
  game::board_2048& gameCore;
  float animation_progress_ = 1.0f;
  animation::Animator animatorFunc =
      animation::Animator(&animation_progress_);
  std::vector<core::animationTiles> animationTiles_;
  core::Direction dir_ = core::Direction::Unset;
};
