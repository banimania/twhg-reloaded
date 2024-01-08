#include "wallblock.hpp"

void WallBlock::tick(Player* player) {
  GameObject::tick(player);
  DrawRectangle(rect.x, rect.y, rect.width, rect.height, outlineColor);
  DrawRectangle(rect.x + 5, rect.y + 5, rect.width - 10, rect.height - 10, fillColor);
}
