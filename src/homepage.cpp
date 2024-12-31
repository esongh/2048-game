#pragma once

#include "homepage.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;

homepage::homepage() 
{
  gameUi = std::make_shared<GameUi>(board_);
}

void homepage::startGame()
{
  auto screen = ftxui::ScreenInteractive::FitComponent();
  int boardSize = board_.get_size();

  Component layout =
      Container::Vertical({Renderer(
                               []() {
                                 return vbox(text("2048")) | size(WIDTH, GREATER_THAN, 3) |
                                        bgcolor(Color::SkyBlue1)| center | vcenter;
                               }),
                           gameUi,
                           Button("Start", [&]() {gameUi->TakeFocus();}) |
                               size(WIDTH, EQUAL, 10) | center | vcenter,
                           Button("Esc", screen.ExitLoopClosure())}) |
      CatchEvent(
          [&](Event e)
          {
            if (e == Event::Escape)
            {
              screen.ExitLoopClosure()();
              return true;
            }
            return false;
          });

  screen.Loop(layout);
}
