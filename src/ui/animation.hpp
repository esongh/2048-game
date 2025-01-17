#include <chrono>
#include <cmath>
#include <vector>

#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"

namespace ui
{
struct animationOptions
{
	int length;
	int tile_size;
	int sep_size;
	std::vector<int> tiles;
	std::vector<float> tile_start;
	bool tail_first = false;
};

class TileBase : public ftxui::Node
{
 public:
  explicit TileBase(int number, int size, ftxui::Color col);
  void ComputeRequirement() override;
  void Render(ftxui::Screen& screen) override;

 private:
  int n;
  int cell_size;
  ftxui::Color num_col;
};

class RowBase : public ftxui::Node
{
 public:
	explicit RowBase(animationOptions options);
	void ComputeRequirement() override;
	void SetBox(ftxui::Box box) override;
	void Render(ftxui::Screen& screen) override;

 private:
	animationOptions options_;
};

class ColumnBase : public ftxui::Node
{
 public:
	explicit ColumnBase(animationOptions options);
	void ComputeRequirement() override;
	void SetBox(ftxui::Box box) override;
	void Render(ftxui::Screen& screen) override;

 private:
	animationOptions options_;
};

inline ftxui::Element tileBase(int number, int size, ftxui::Color col) {
  return std::make_shared<TileBase>(number, size, col);
}

inline ftxui::Element rowBase(animationOptions optoins)
{
	return std::make_shared<RowBase>(optoins);
}

inline ftxui::Element columnBase(animationOptions optoins)
{
	return std::make_shared<ColumnBase>(optoins);
}
} // namespace ui
