#include <filesystem>
#include <vector>
#include <memory>

#include "ftxui/component/animation.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/screen.hpp"
#include "tile.hpp"

using namespace ui;

class tileEle : public ftxui::Node
{
 public:
  explicit tileEle(std::vector<ColorRGBA>& data, std::uint16_t size) : size_(size), data_(data) {}

  void ComputeRequirement() override
  {
    requirement_.min_x = size_;
    requirement_.min_y = size_ / 2;
  }
  
  void Render(ftxui::Screen& screen) override
  {
    for (int cur_y = 0; cur_y < size_ / 2; ++cur_y)
    {
      for (int cur_x = 0; cur_x < size_; ++cur_x)
      {
        int top_index = cur_y * 2 * size_ + cur_x;
        const auto& top_color = data_[top_index];
        const auto& bottom_color = data_[top_index + size_];

        auto& pixel = screen.PixelAt(box_.x_min + cur_x, box_.y_min + cur_y);
        pixel.character = "▀";
        pixel.foreground_color = ftxui::Color(top_color.r, top_color.g, top_color.b);
        pixel.background_color = ftxui::Color(bottom_color.r, bottom_color.g, bottom_color.b);
      }
    }
  }

  std::vector<ColorRGBA> data_;

 private:
  std::uint16_t size_;
};

class animComp : public ftxui::ComponentBase
{
 public:
  animComp(std::vector<ColorRGBA>& data, std::uint16_t size)
  {
    element_ = std::make_shared<tileEle>(data, size);
    box_ = ftxui::Box{.x_min = 0, .x_max = 31, .y_min = 0, .y_max = 31};
  };

  void OnAnimation(ftxui::animation::Params& params) override
  {
    if (animatorFunc.to() != 0.0f)
    {
      animatorFunc.OnAnimation(params);
    }
  }

  ftxui::Element Render() override
  {
    auto box = ftxui::Box{.x_min = 0, .x_max = 15, .y_min = 0, .y_max = 15};
    element_->SetBox(box);
    return element_;
  }

 private:
  ftxui::Box box_;
  std::shared_ptr<tileEle> element_;
  float animation_progress_ = 1.0f;
  ftxui::animation::Animator animatorFunc = ftxui::animation::Animator(&animation_progress_);
};

std::vector<TileSet> splitTileSet(const TileSet& tileSet)
{
  std::uint32_t height = tileSet.size().height;
  std::uint32_t width = tileSet.size().width;

  std::uint32_t num = height / width;

  std::vector<TileSet> result;
  result.reserve(num);
  for (std::uint32_t i = 0; i < num; ++i)
  {
    result.emplace_back(TileSize{width, width});
    result.back().data_ = {tileSet.data_.begin() + i * width * width,
                           tileSet.data_.begin() + (i + 1) * width * width};
  }

  return result;
}

int main()
{
  auto current_path = std::filesystem::current_path();
  std::string asset_file = "D:/Workspace/playyard/cpp-game/2048-game/art_asset/texture_slim.png";
  const auto tileSet = ui::load_png(asset_file);

  auto tiles = splitTileSet(tileSet);

  std::vector<ColorRGBA> data{tiles[1].data_};
  std::uint16_t png_size = static_cast<std::uint16_t>(tileSet.size().width);
  auto tilecolor = std::make_shared<tileEle>(data, png_size);
  ftxui::Elements children;
  for (const auto& data : tiles)
  {
    std::vector<ColorRGBA> data_color{data.data_};
    children.push_back(std::make_shared<tileEle>(data_color, png_size));
    children.push_back(ftxui::separator());
  }
  children.pop_back();
  auto box = ftxui::hbox({children});
  auto window = ftxui::window(ftxui::text("Title"), box);
  auto screen = ftxui::Screen::Create(ftxui::Dimension::Fit(window), ftxui::Dimension::Fit(window));
  window->Render(screen);
  screen.Print();

  return 0;
}
