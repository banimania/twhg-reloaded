#include "wallblock.hpp"

void WallBlock::tick() {
  DrawRectangle(x, y, width, height, outlineColor);
  DrawRectangle(x + 5, y + 5, width - 10, height - 10, fillColor);
}
