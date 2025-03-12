#pragma once

#include "homepage.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;

homepage::homepage() { gameUi = std::make_shared<GameUi>(board_); }

void homepage::startGame()
{
  auto screen = ftxui::ScreenInteractive::FitComponent();
  int boardSize = board_.get_size();

  Component layout = Container::Vertical({gameUi}) |
                     CatchEvent(
                         [&](Event e)
                         {
                           if (e == Event::Escape)
                           {
                             screen.ExitLoopClosure()();
                             return true;
                           }
                           return gameUi->OnEvent(e);
                         });

  screen.Loop(layout);
}
