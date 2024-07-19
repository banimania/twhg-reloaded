#include "fog.hpp"
#include "../../../utils/needed.hpp"

void FogBlock::tick(Player* player) {
  GameObject::tick(player);
  if (TWHGReloaded::state == EDITOR || visible) DrawRectangle(rect.x, rect.y, rect.width, rect.height, {0, 0, 0, 100});
}

FogBlock* FogBlock::clone() {
  FogBlock* clone = new FogBlock({rect.x, rect.y}, level, zLayer);
  clone->rect = rect;
  clone->pathIds = pathIds;
  clone->visible = visible;
  clone->radius = radius;
  return clone;
}
