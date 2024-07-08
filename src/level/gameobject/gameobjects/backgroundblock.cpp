#include "backgroundblock.hpp"

void BackgroundBlock::tick(Player* player) {
  GameObject::tick(player);
  DrawRectangle(rect.x, rect.y, rect.width, rect.height, wallBlockColorFill);
}

BackgroundBlock* BackgroundBlock::clone() {
  BackgroundBlock* clone = new BackgroundBlock({rect.x, rect.y}, level, zLayer);
  clone->rect = rect;
  clone->paths = paths;
  return clone;
}
