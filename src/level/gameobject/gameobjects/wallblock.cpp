#include "wallblock.hpp"
#include <raylib.h>

void WallBlock::tick(Player* player) {
  GameObject::tick(player);
  DrawRectangle(rect.x, rect.y, rect.width, rect.height, wallBlockColorFill);


  if (states[0]) DrawRectangle(rect.x, rect.y + wallThickness, wallThickness, rect.height - 2 * wallThickness, wallBlockColorOutline);

  if (states[1]) DrawRectangle(rect.x + wallThickness, rect.y, rect.width - 2 * wallThickness, wallThickness, wallBlockColorOutline);

  if (states[2]) DrawRectangle(rect.x + rect.width - wallThickness, rect.y + wallThickness, wallThickness, rect.height - 2 * wallThickness, wallBlockColorOutline);

  if (states[3]) DrawRectangle(rect.x + wallThickness, rect.y + rect.height - wallThickness, rect.width - 2 * wallThickness, wallThickness, wallBlockColorOutline);

  if (states[4]) DrawRectangle(rect.x, rect.y, wallThickness, wallThickness, wallBlockColorOutline);

  if (states[5]) DrawRectangle(rect.x + rect.width - wallThickness, rect.y, wallThickness, wallThickness, wallBlockColorOutline);

  if (states[6]) DrawRectangle(rect.x, rect.y + rect.height - wallThickness, wallThickness, wallThickness, wallBlockColorOutline);

  if (states[7]) DrawRectangle(rect.x + rect.width - wallThickness, rect.y + rect.height - wallThickness, wallThickness, wallThickness, wallBlockColorOutline);
}

void WallBlock::updateWallBlock(std::vector<WallBlock*> wallBlocks) {
  for (int i = 0; i < 8; i++) {
    states[i] = true;
  }

  bool d1 = false;
  bool d2 = false;
  bool d3 = false;
  bool d4 = false;

  for (WallBlock* wallBlock : wallBlocks) {
    if (wallBlock->rect.x + 40 == rect.x && wallBlock->rect.y == rect.y) states[0] = false;
    if (wallBlock->rect.x - 40 == rect.x && wallBlock->rect.y == rect.y) states[2] = false;
    if (wallBlock->rect.x == rect.x && wallBlock->rect.y + 40 == rect.y) states[1] = false;
    if (wallBlock->rect.x == rect.x && wallBlock->rect.y - 40 == rect.y) states[3] = false;

    if (wallBlock->rect.x - 40 == rect.x && wallBlock->rect.y - 40 == rect.y) d1 = true;
    if (wallBlock->rect.x + 40 == rect.x && wallBlock->rect.y - 40 == rect.y) d2 = true;
    if (wallBlock->rect.x - 40 == rect.x && wallBlock->rect.y + 40 == rect.y) d3 = true;
    if (wallBlock->rect.x + 40 == rect.x && wallBlock->rect.y + 40 == rect.y) d4 = true;
  }

  if (d1 && !states[2] && !states[3]) states[7] = false;
  if (d2 && !states[0] && !states[3]) states[6] = false;
  if (d3 && !states[1] && !states[2]) states[5] = false;
  if (d4 && !states[0] && !states[1]) states[4] = false;
}

WallBlock* WallBlock::clone() {
  WallBlock* clone = new WallBlock({rect.x, rect.y}, level, zLayer);
  clone->rect = rect;
  clone->paths = paths;
  return clone;
}
