#include <algorithm>
#include <array>
#include <format>

#include "ftxui/screen/color.hpp"

using namespace ftxui::literals;

namespace ui
{
inline ftxui::Color color_of(int num)
{
  switch (num)
  {
    case 0:
      return ftxui::Color::GrayDark;
    case 2:
      return 0x4db6ac_rgb;
    case 4:
      return 0x66bb6a_rgb;
    case 8:
      return 0x8bc34a_rgb;
    case 16:
      return 0xc0ca33_rgb;
    case 32:
      return 0xfbc02d_rgb;
    case 64:
      return 0xff8f00_rgb;
    case 128:
      return 0xe64a19_rgb;
    case 256:
      return 0xbf360c_rgb;
    case 512:
      return 0x795548_rgb;
    case 1024:
      return 0x4e342e_rgb;
    default:
      return ftxui::Color::GrayDark;
  }
}

inline std::string numToStr(int num, bool fun = false)
{
  if (!fun)
  {
    if (num == 0)
    {
      return " ";
    }
    return std::format("{0}", num);
  }

  std::array<std::pair<int, std::string>, 11> map{{{0, " "},
                                                   {2, "王"},
                                                   {4, "雨"},
                                                   {8, "欣"},
                                                   {16, "是"},
                                                   {32, "大"},
                                                   {64, "憨"},
                                                   {128, "包"},
                                                   {256, "大"},
                                                   {512, "宝"},
                                                   {1024, "贝"}}};

  const auto found =
      std::find_if(map.begin(), map.end(), [num](const auto& m) { return m.first == num; });
  return std::format("{: ^6}", found->second);
}
}  // namespace ui
