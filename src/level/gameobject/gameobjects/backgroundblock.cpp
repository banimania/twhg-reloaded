#include "backgroundblock.hpp"

void BackgroundBlock::tick(Player* player) {
  GameObject::tick(player);
  DrawRectangle(rect.x, rect.y, rect.width, rect.height, wallBlockColorFill);
}
