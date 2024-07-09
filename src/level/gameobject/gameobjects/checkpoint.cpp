#include "checkpoint.hpp"
#include <raylib.h>

void Checkpoint::tick(Player* player) {
  GameObject::tick(player);
  DrawRectangleRec(rect, fillColor);
}

Checkpoint* Checkpoint::clone() {
  Checkpoint* clone = new Checkpoint({rect.x, rect.y}, goal, level, zLayer);
  clone->rect = rect;
  clone->paths = paths;
  return clone;
}
