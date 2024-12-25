
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"
#include "row_merge.hpp"
#include "homepage.hpp"

using namespace ftxui;

using TypeBoard = std::vector<std::vector<int>>;

float animation_progress = 1.0f;

namespace
{
inline ftxui::Color color_of(int num)
{
  switch (num)
  {
    case 0:
      return ftxui::Color::Grey50;
    case 2:
      return ftxui::Color::GrayDark;
    case 4:
      return ftxui::Color::GrayLight;
    case 8:
      return ftxui::Color::Yellow;
    default:
      return ftxui::Color::CyanLight;
  }
}
ftxui::Element board_view(const game::board_2048& board)
{
  Elements rows;
  for (uint16_t i = 0; i < board.get_size(); ++i)
  {
    Elements cols;
    for (uint16_t j = 0; j < board.get_size(); ++j)
    {
      cols.push_back(hbox(text(std::to_string(board.get_tile(i, j))) | center | borderRounded |
                          color(color_of(board.get_tile(i, j))) | size(WIDTH, EQUAL, 5) |
                          size(HEIGHT, EQUAL, 3)));
    }
    rows.push_back(ftxui::hbox(cols));
  }
  return vbox(rows) | borderRounded;
}
}  // namespace

class BoardBase : public ftxui::ComponentBase
{
 public:
  BoardBase(TypeBoard board) : board_(board) {}

  ftxui::Element Render() override
  {
    Elements rows;
    for (auto row : board_)
    {
      Elements cols;
      for (auto col : row)
      {
        cols.push_back(hbox(text(std::to_string(col))) | borderRounded | color(color_of(col)) |
                       size(WIDTH, EQUAL, 4) | size(HEIGHT, EQUAL, 3));
      }
      rows.push_back(ftxui::hbox(cols));
    }
    return ftxui::window(ftxui::text("home"), ftxui::vbox(rows));
  }

 private:
  TypeBoard board_;
};

class TileBase : public ftxui::Node
{
 public:
  explicit TileBase(int number, int size, ftxui::Color col)
      : n(number), cell_size(size), num_col(col)
  {
  }

  void ComputeRequirement() override
  {
    requirement_.min_x = cell_size * 2;
    requirement_.min_y = cell_size;
  }

  void Render(ftxui::Screen& screen) override
  {
    if (box_.x_max < box_.x_min)
    {
      return;
    }
    for (int x = box_.x_min; x <= box_.x_max; x++)
    {
      for (int y = box_.y_min; y <= box_.y_max; y++)
      {
        screen.PixelAt(x, y).background_color = ftxui::Color::DarkCyan;
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

 private:
  int n;
  int cell_size;
  ftxui::Color num_col;
};

class TileRowBase : public ftxui::Node
{
 public:
  explicit TileRowBase(std::vector<float> tile_pos, std::vector<int> tile_numbers, int row_len,
                       int tileSize, int sep_size = 1)
      : tile_start(tile_pos),
        tiles(tile_numbers),
        length(row_len),
        tile_size(tileSize),
        sep_size(sep_size)
  {
    auto zero = [tileSize]
    { return text(" ") | size(WIDTH, EQUAL, tileSize * 2) | size(HEIGHT, EQUAL, tileSize); };
    auto sep_e = [sep_size]
    {
      return text(" ") | size(WIDTH, EQUAL, sep_size * 2) | size(HEIGHT, EQUAL, sep_size) |
             bgcolor(ftxui::Color::BlueViolet);
    };

    Elements elements;
    elements.reserve(2 * length - 1);
    elements.push_back(zero());
    for (int i = 1; i < length; i++)
    {
      elements.push_back(sep_e());
      elements.push_back(zero());
    }
    children_.push_back(hbox(elements));
  }

  void ComputeRequirement() override
  {
    Node::ComputeRequirement();
    requirement_ = children_[0]->requirement();
  }

  void SetBox(ftxui::Box box) override
  {
    Node::SetBox(box);
    children_[0]->SetBox(ftxui::Box{.x_min = box_.x_min,
                                    .x_max = box_.x_min + requirement_.min_x - 1,
                                    .y_min = box_.y_min,
                                    .y_max = box_.y_min + requirement_.min_y - 1});
  }

  void Render(ftxui::Screen& screen) override
  {
    Node::Render(screen);
    if (box_.x_max < box_.x_min)
    {
      return;
    }
    for (int i = 0; i < tiles.size(); i++)
    {
      auto tile = tile_element(tiles[i]);
      int startX = box_.x_min + int(std::round(tile_start[i]));
      int startY = box_.y_min;
      tile->SetBox(Box{.x_min = startX,
                       .x_max = startX + tile_size * 2 - 1,
                       .y_min = startY,
                       .y_max = startY + tile_size - 1});
      tile->Render(screen);
    }
  }

 private:
  std::vector<float> tile_start;
  std::vector<int> tiles;
  int length;
  int tile_size;
  int sep_size;

  Element tile_element(int number) const 
  { 
    return Make<TileBase>(number, tile_size, color_of(2));
  }
};

class RowComponent : public ftxui::ComponentBase
{
 public:
  RowComponent() : box_({0, 0, 0, 0}) {}

  void OnAnimation(ftxui::animation::Params& params) override
  {
    if (!started)
    {
      return;
    }
    if (animatorFunc.to() != 0.0f)
    {
      animatorFunc.OnAnimation(params);
    }
  }

  bool OnEvent(ftxui::Event event) override
  {
    if (event == ftxui::Event::Backspace)
    {
      if (animation_progress == 1.0f)
      {
        animation_progress = 0.0f;
        animatorFunc =
            ftxui::animation::Animator(&animation_progress, 1.0f, std::chrono::milliseconds(1000));
      }

      return true;
    }
    if (event == ftxui::Event::Return)
    {
      if (!started)
      {
        animatorFunc = ftxui::animation::Animator(&animation_progress, 1.0f,
                                                  std::chrono::milliseconds(1000));
        started = true;
      }
      return true;
    }

    return false;
  }

  ftxui::Element Render() override
  {
    Elements rows;
    tile_pos.push_back((cell_size + sep_size) * 2 * std::lerp(0.0, 2.0, animation_progress));
    tile_numbers.push_back(1);
    tile_pos.push_back((cell_size + sep_size) * 2 * std::lerp(2.0, 3.0, animation_progress));
    tile_numbers.push_back(2);
    rows.push_back(Make<TileRowBase>(tile_pos, tile_numbers, board_size, cell_size, sep_size));
    tile_pos.clear();
    tile_numbers.clear();
    return vbox(rows) | borderRounded | bgcolor(Color::CyanLight);
  }

 private:
  bool started = false;
  int board_size = 4;
  int cell_size = 5;
  int sep_size = 1;
  ftxui::Box box_;
  float animation_progress = 0.0f;
  ftxui::animation::Animator animatorFunc = ftxui::animation::Animator(&animation_progress, 0.0f,
                                                                      std::chrono::milliseconds(1000));

  std::vector<float> tile_pos;
  std::vector<int> tile_numbers;
  std::tuple<int, float, float> row_info = {1, 0.0, 3.0};
};

void PrintVec(std::vector<int> v)
{
  for (int i = 0; i < v.size(); i++)
  {
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
}

void PrintMatrix(std::vector<std::vector<int>> v)
{
  for (int i = 0; i < v.size(); i++)
  {
    PrintVec(v[i]);
  }
}

int main()
{
  auto game = homepage();
  game.startGame();

  return 0;
}
