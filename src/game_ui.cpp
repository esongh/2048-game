#pragma once

#include "game_ui.hpp"

#include "animation.hpp"
#include "core/game_core.hpp"
#include "theme.hpp"

using namespace ftxui;

void GameUi::OnAnimation(animation::Params& params)
{
  if (animatorFunc.to() != 0.0f)
  {
    animatorFunc.OnAnimation(params);
  }
}

Element GameUi::Render()
{
  Element ret;
  if (animation_progress_ == 1.0f)
  {
    Elements rows;
    for (int i = 0; i < gameCore.get_size(); i++)
    {
      Elements tiles;
      for (int j = 0; j < gameCore.get_size(); j++)
      {
        const auto num = gameCore.get_tile(i, j);
        const std::string numStr = num == 0 ? " " : std::to_string(num);
        tiles.push_back(hbox(text(numStr) | color(Color::White)) | center | borderRounded |
                        color(ui::color_of(num)) | size(WIDTH, EQUAL, 6) | size(HEIGHT, EQUAL, 3));
        tiles.push_back(separatorEmpty() | size(WIDTH, EQUAL, 2));
      }
      tiles.pop_back();
      rows.push_back(ftxui::hbox(tiles));
      rows.push_back(separatorEmpty() | size(HEIGHT, EQUAL, 1));
    }
    rows.pop_back();
    ret = vbox(rows) | borderRounded;
  }
  else
  {
    auto PopulateRowOrCol = [](ui::animationOptions& opt, core::Direction dir, Elements& sequence)
    {
      if (dir == core::Direction::LEFT || dir == core::Direction::RIGHT)
      {
        sequence.push_back(ui::rowBase(opt));
        sequence.push_back(separatorEmpty() | size(HEIGHT, EQUAL, 1));
      }
      else
      {
        sequence.push_back(ui::columnBase(opt));
        sequence.push_back(separatorEmpty() | size(WIDTH, EQUAL, 2));
      }
    };

    Elements sequence;
    for (auto row : animationTiles_)
    {
      Elements tiles;
      ui::animationOptions opt;
      opt.length = row.preNum.size();
      opt.tile_size = 3;
      opt.sep_size = 1;
      int scale = 1;
      if (dir_ == core::Direction::LEFT || dir_ == core::Direction::RIGHT)
      {
        scale = 2;
      }

      const auto step_size = (opt.tile_size + opt.sep_size) * scale;
      for (int i = 0; i < row.preNum.size(); i++)
      {
        const auto num = row.preNum[i];
        const auto found = std::find_if(row.slideDistance.begin(), row.slideDistance.end(),
                                        [i](const auto& m) { return m.from == i; });
        float position = 0.0f;
        if (found != row.slideDistance.end())
        {
          position = (found->from - found->step * animation_progress_) * step_size;
        }
        else
        {
          position = i * step_size;
        }

        if (dir_ == core::Direction::RIGHT || dir_ == core::Direction::DOWN)
        {
          position = (opt.length - 1) * step_size - position;
        }

        opt.tile_start.push_back(position);
        opt.tiles.push_back(num);
      }
      PopulateRowOrCol(opt, dir_, sequence);
    }
    sequence.pop_back();

    ret = [dir = dir_, sequence]()
    {
      if (dir == core::Direction::LEFT || dir == core::Direction::RIGHT)
      {
        return vbox(sequence);
      }
      else
      {
        return hbox(sequence);
      }
    }() | borderRounded;
  }

  int col_size = (3 + 1) * 4 - 1;
  return ret | size(WIDTH, EQUAL, col_size * 2 + 2) | size(HEIGHT, EQUAL, col_size + 2) |
         reflect(box_);
}

bool GameUi::OnEvent(Event e)
{
  dir_ = core::Direction::Unset;
  if (e == Event::ArrowLeft)
  {
    dir_ = core::Direction::LEFT;
  }
  else if (e == Event::ArrowRight)
  {
    dir_ = core::Direction::RIGHT;
  }
  else if (e == Event::ArrowUp)
  {
    dir_ = core::Direction::UP;
  }
  else if (e == Event::ArrowDown)
  {
    dir_ = core::Direction::DOWN;
  }
  else
  {
    return false;
  }

  if (dir_ != core::Direction::Unset)
  {
    if (animation_progress_ != 1.0f)
    {
      return false;
    }

    gameCore.move(dir_);
    animationTiles_.clear();
    animationTiles_ = gameCore.get_animationTiles();
    if (dir_ == core::Direction::RIGHT || dir_ == core::Direction::UP)
    {
      std::reverse(animationTiles_.begin(), animationTiles_.end());
    }
    animation_progress_ = 0.0f;
    animatorFunc = animation::Animator(&animation_progress_, 1.0f, std::chrono::milliseconds(250));
    return true;
  }
  return false;
}
