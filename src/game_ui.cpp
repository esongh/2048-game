#pragma once

#include "game_ui.hpp"
#include "ui/theme.hpp"

using namespace ftxui;

void GameUi::OnAnimation(animation::Params& params)
{
  if (animatorFunc.to() != 1.0f)
  {
    animatorFunc.OnAnimation(params);
  }
}

Element GameUi::Render()
{
  Elements rows;
  for (int i = 0; i < gameCore.get_size(); i++)
  {
    Elements cols;
    for (int j = 0; j < gameCore.get_size(); j++)
    {
      const auto num = gameCore.get_tile(i, j);
      const std::string numStr = num ==0 ? " " : std::to_string(num);
      cols.push_back(hbox(text(numStr) | center | borderRounded |
                          color(ui::color_of(num)) | size(WIDTH, EQUAL, 5) |
                          size(HEIGHT, EQUAL, 3)));
    }
    rows.push_back(ftxui::hbox(cols));
  }
  return vbox(rows) | borderRounded;
}

bool GameUi::OnEvent(Event e)
{
  if (e.is_mouse() && e.mouse().motion == Mouse::Pressed)
  {
    TakeFocus();
  }

  auto dir = core::Direction::Unset;
  if (e == Event::ArrowLeft)
  {
    dir = core::Direction::LEFT;
  }
  else if (e == Event::ArrowRight)
  {
    dir = core::Direction::RIGHT;
  }
  else if (e == Event::ArrowUp)
  {
    dir = core::Direction::UP;
  }
  else if (e == Event::ArrowDown)
  {
    dir = core::Direction::DOWN;
  }
  else
  {
    return false;
  }

  if (dir != core::Direction::Unset)
  {
    gameCore.move(dir);
    animation_progress = 0.0f;
    animatorFunc = animation::Animator(&animation_progress, 1.0f, std::chrono::milliseconds(500));
    return true;
  }
  return false;
}
