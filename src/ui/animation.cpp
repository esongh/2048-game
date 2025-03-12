
#pragma once
#include "animation.hpp"
#include "theme.hpp"

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"

using namespace ftxui;
Decorator quadrate(int width, int height, ftxui::Color col)
{
  return ftxui::size(WIDTH, EQUAL, width * 2) | ftxui::size(HEIGHT, EQUAL, height) | ftxui::color(col);
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
  // for (int x = box_.x_min; x <= box_.x_max; x++)
  // {
  //   for (int y = box_.y_min; y <= box_.y_max; y++)
  //   {
  //     screen.PixelAt(x, y).background_color = num_col;
  //   }
  // }

  int mid_y = (box_.y_min + box_.y_max) / 2;
  std::string n_char = ui::numToStr(n);
  std::string numStr = std::format("{0:^{1}}", n_char, box_.x_max - box_.x_min + 1);
  auto it = numStr.begin();
  for (int x = box_.x_min; x <= box_.x_max; x++)
  {
    auto& pixel = screen.PixelAt(x, mid_y);
    pixel.character = *it++;
    pixel.foreground_color = ftxui::Color::White;
  }
}

RowBase::RowBase(animationOptions options) : options_(options)
{
  Elements tiles;
  tiles.reserve(options_.length * 2 + 1);
  for (int i = 0; i < options_.length; i++)
  {
    tiles.push_back(text(" ") |
                    quadrate(options_.tile_size, options_.tile_size, ftxui::Color::GrayDark));
    tiles.push_back(separatorEmpty() |
                    quadrate(options_.sep_size, options_.tile_size, ftxui::Color::GrayDark));
  }
  children_.push_back(hbox(tiles));
}

void RowBase::ComputeRequirement()
{
  Node::ComputeRequirement();
  requirement_ = children_[0]->requirement();
}

void RowBase::SetBox(ftxui::Box box)
{
  Node::SetBox(box);
  children_[0]->SetBox(ftxui::Box{.x_min = box.x_min,
                                  .x_max = box.x_min + requirement_.min_x - 1,
                                  .y_min = box.y_min,
                                  .y_max = box.y_min + requirement_.min_y - 1});
}

void RowBase::Render(ftxui::Screen& screen)
{
  Node::Render(screen);
  if (box_.x_max < box_.x_min)
  {
    return;
  }
  for (int i = 0; i < options_.tiles.size(); i++)
  {
    const auto num = options_.tiles[i];
    auto tile = tileBase(num, options_.tile_size, Color::White) | bgcolor(ui::color_of(num));
    int start_x = box_.x_min + int(std::round(options_.tile_start[i]));
    int start_y = box_.y_min;
    tile->SetBox(ftxui::Box{.x_min = start_x,
                            .x_max = start_x + options_.tile_size * 2 - 1,
                            .y_min = start_y,
                            .y_max = start_y + options_.tile_size - 1});
    tile->Render(screen);
  }
}

ColumnBase::ColumnBase(animationOptions options) : options_(options)
{
  Elements tiles;
  tiles.reserve(options_.length * 2 + 1);
  for (int i = 0; i < options_.length; i++)
  {
    tiles.push_back(text(" ") |
                    quadrate(options_.tile_size, options_.tile_size, ftxui::Color::GrayDark));
    tiles.push_back(text(" ") |
                    quadrate(options_.tile_size, options_.sep_size, ftxui::Color::GrayDark));
  }
  children_.push_back(vbox(tiles));
}

void ColumnBase::ComputeRequirement()
{
  Node::ComputeRequirement();
  requirement_ = children_[0]->requirement();
}

void ColumnBase::SetBox(ftxui::Box box)
{
  Node::SetBox(box);
  children_[0]->SetBox(ftxui::Box{.x_min = box.x_min,
                                  .x_max = box.x_min + requirement_.min_x - 1,
                                  .y_min = box.y_min,
                                  .y_max = box.y_min + requirement_.min_y - 1});
}

void ColumnBase::Render(ftxui::Screen& screen)
{
  Node::Render(screen);
  if (box_.x_max < box_.x_min)
  {
    return;
  }
  for (int i = 0; i < options_.tiles.size(); i++)
  {
    const auto num = options_.tiles[i];
    auto tile = tileBase(num, options_.tile_size, Color::White) | bgcolor(ui::color_of(num));
    int start_x = box_.x_min;
    int start_y = box_.y_min + int(std::round(options_.tile_start[i]));
    tile->SetBox(ftxui::Box{.x_min = start_x,
                            .x_max = start_x + options_.tile_size * 2 - 1,
                            .y_min = start_y,
                            .y_max = start_y + options_.tile_size - 1});
    tile->Render(screen);
  }
}
}  // namespace ui
