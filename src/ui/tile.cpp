#pragma once
#include "tile.hpp"

#include "lodepng.h"

namespace ui
{
TileSet load_png(const std::filesystem::path& filename)
{
  std::vector<unsigned char> image;
  unsigned width, height;
  unsigned error = lodepng::decode(image, width, height, filename.string());
  if (error)
  {
    throw std::runtime_error("Error while loading PNG file: " + std::to_string(error));
  }
  TileSet art_asset({width, height});
  
  for (std::size_t y = 0; y < height; ++y)
  {
    for (std::size_t x = 0; x < width; ++x)
    {
      auto& color = art_asset.at(x, y);
      color.r = image[4 * width * y + 4 * x + 0];
      color.g = image[4 * width * y + 4 * x + 1];
      color.b = image[4 * width * y + 4 * x + 2];
      color.a = image[4 * width * y + 4 * x + 3];
    }
  }
  
  return art_asset;
}
} // namespace ui
