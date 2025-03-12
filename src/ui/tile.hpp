#include <cstdint>
#include <filesystem>

namespace ui
{
struct TileSize
{
  std::size_t width;
  std::size_t height;
};

struct ColorRGBA
{
  std::uint8_t r;
  std::uint8_t g;
  std::uint8_t b;
  std::uint8_t a;
};

class TileSet
{
public:
  inline explicit TileSet(const TileSize& size) : size_(size)
  {
    data_.resize(size.width * size.height);
  }
  
  inline [[nodiscard]] const ColorRGBA& at(const std::size_t x, const std::size_t y) const
  {
    return data_[y * size_.width + x];
  }
  
  inline [[nodiscard]] ColorRGBA& at(const std::size_t x, const std::size_t y)
  {
    return data_[y * size_.width + x];
  }
  
  inline [[nodiscard]] const TileSize& size() const
  {
    return size_;
  }

  std::vector<ColorRGBA> data_;
private:
  TileSize size_;
};

TileSet load_png(const std::filesystem::path& filename);
} // namespace ui
