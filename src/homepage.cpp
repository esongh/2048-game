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

  Component layout =
      Container::Vertical({Renderer(
                               []() {
                                 return vbox(text("2048")) | size(WIDTH, GREATER_THAN, 3) |
                                        bgcolor(Color::SkyBlue1)| center | vcenter;
                               }),
                           Renderer([&]() 
                           { 
                              return vbox(game_view()) | borderRounded; 
                           }),
                           Button("Esc", screen.ExitLoopClosure())}) |
      CatchEvent(
          [&](Event e)
          {
            if (e == Event::Escape)
            {
              screen.ExitLoopClosure()();
              return true;
            }
            else if (e == Event::ArrowLeft)
            {
              move(core::Direction::LEFT);
              return true;
            }
            return false;
          });

  screen.Loop(layout);
}

Element homepage::game_view()
{
  Elements rows;
  for (int i = 0; i < board_.get_size(); i++)
  {
    Elements cols;
    for (int j = 0; j < board_.get_size(); j++)
    {
      const auto num = board_.get_tile(i, j);
      cols.push_back(hbox(text(std::to_string(num)) | center | borderRounded |
                          color(ui::color_of(num)) | size(WIDTH, EQUAL, 5) |
                          size(HEIGHT, EQUAL, 3)));
    }
    rows.push_back(ftxui::hbox(cols));
  }
  return vbox(rows) | borderRounded;
}

void homepage::move(core::Direction dir)
{
  board_.move(dir);
}
