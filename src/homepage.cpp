#pragma once

#include "homepage.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

#include "game_core.hpp"
#include "theme.hpp"

using namespace ftxui;

homepage::homepage() {}

void homepage::startGame()
{
  auto screen = ftxui::ScreenInteractive::FitComponent();
  int boardSize = board_.get_size();

  Elements rows;
  for (int i = 0; i < boardSize; i++)
  {
    Elements col;
    for (int j = 0; j < boardSize; j++)
    {
      int num = board_.get_tile(i, j);
      col.push_back(hbox(text(std::to_string(num)) | center | borderRounded |
                         color(ui::color_of(num)) | size(WIDTH, EQUAL, 5) |
                         size(HEIGHT, EQUAL, 3)));
    }
    rows.push_back(ftxui::hbox(col));
  }

  Component layout =
      Container::Vertical({Renderer(
                               []() {
                                 return vbox(text("2048") | center) | size(WIDTH, EQUAL, 10) |
                                        bgcolor(Color::SkyBlue1);
                               }),
                           Renderer([&rows]() { return vbox(rows) | borderRounded; }),
                           Button("Esc", screen.ExitLoopClosure())}) |
      CatchEvent(
          [&screen](Event e)
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
