
#pragma once
#include "animation.hpp"

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"

using namespace ftxui;
Decorator quadrate(int size)
{
  return ftxui::size(WIDTH, EQUAL, size *2) | ftxui::size(HEIGHT, EQUAL, size);
}

namespace ui
{

TileBase::TileBase(int number, int size, ftxui::Color col)
    : n(number), cell_size(size), num_col(col)
{
}

void TileBase::ComputeRequirement()
{
  requirement_.min_x = cell_size * 2;
  requirement_.min_y = cell_size;
}

void TileBase::Render(ftxui::Screen& screen)
{
  if (box_.x_max < box_.x_min)
  {
    return;
  }
  for (int x = box_.x_min; x <= box_.x_max; x++)
  {
    for (int y = box_.y_min; y <= box_.y_max; y++)
    {
      screen.PixelAt(x, y).background_color = ftxui::Color::GrayDark;
    }
  }

  int mid_y = (box_.y_min + box_.y_max) / 2;
  std::string numStr = std::format("{0:^{1}}", n, box_.x_max - box_.x_min + 1);
  auto it = numStr.begin();
  for (int x = box_.x_min; x <= box_.x_max; x++)
  {
    auto& pixel = screen.PixelAt(x, mid_y);
    pixel.character = *it++;
    pixel.foreground_color = num_col;
  }
}

RowBase::RowBase(animationOptions options) : options_(options)
{
  Elements tiles;
  tiles.reserve(options_.length * 2 + 1);
  for (int i = 0; i < options_.length; i++)
  {
    tiles.push_back(text(" ") | quadrate(options_.tile_size));
    tiles.push_back(text(" ") | quadrate(options_.sep_size));
  }
  children_.push_back(hbox(tiles));
}

void RowBase::ComputeRequirement()
{
  Node::ComputeRequirement();
  requirement_ = children_[0]->requirement();
}

void RowBase::Render(ftxui::Screen& screen) {}
}  // namespace ui
