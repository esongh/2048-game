
#include <iostream>
#include <vector>

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"
#include "game.hpp"
#include "row_merge.hpp"

using namespace ftxui;

using TypeBoard = std::vector<std::vector<int>>;

namespace
{
inline ftxui::Color color_of(int num)
{
  switch (num)
  {
    case 0:
      return ftxui::Color::Red;
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
  return vbox(rows);
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
  game::board_2048 board(4);
  auto view = board_view(board);
  auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(view));
  Render(screen, view);
  screen.Print();
  return 0;
}
