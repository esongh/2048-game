#include "ftxui/screen/color.hpp"

namespace ui
{
ftxui::Color color_of(int num)
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

}
