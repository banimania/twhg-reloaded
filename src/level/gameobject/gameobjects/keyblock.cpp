#include "keyblock.hpp"
#include "../../level.hpp"
#include "key.hpp"

void KeyBlock::tick(Player* player) {
  GameObject::tick(player);

  if (isOpening) {
    
    Color alphaOutlineColor = {outlineColor.r, outlineColor.g, outlineColor.b, (static_cast<unsigned char>((1 - openTimer / openTime) * 255.0f))};

    DrawRectangle(rect.x, rect.y, rect.width, rect.height, fillColor);
    if (states[0]) DrawRectangle(rect.x, rect.y + wallThickness, wallThickness, rect.height - 2 * wallThickness, alphaOutlineColor);

    if (states[1]) DrawRectangle(rect.x + wallThickness, rect.y, rect.width - 2 * wallThickness, wallThickness, alphaOutlineColor);

    if (states[2]) DrawRectangle(rect.x + rect.width - wallThickness, rect.y + wallThickness, wallThickness, rect.height - 2 * wallThickness, alphaOutlineColor);

    if (states[3]) DrawRectangle(rect.x + wallThickness, rect.y + rect.height - wallThickness, rect.width - 2 * wallThickness, wallThickness, alphaOutlineColor);

    if (states[4]) DrawRectangle(rect.x, rect.y, wallThickness, wallThickness, alphaOutlineColor);

    if (states[5]) DrawRectangle(rect.x + rect.width - wallThickness, rect.y, wallThickness, wallThickness, alphaOutlineColor);

    if (states[6]) DrawRectangle(rect.x, rect.y + rect.height - wallThickness, wallThickness, wallThickness, alphaOutlineColor);

    if (states[7]) DrawRectangle(rect.x + rect.width - wallThickness, rect.y + rect.height - wallThickness, wallThickness, wallThickness, alphaOutlineColor);

    openTimer += GetFrameTime();
    if (openTimer > openTime) {
      isOpening = false;
      openTimer = 0.0f;
    }
  }
  if (open) return;

  GameObject::tick(player);
  DrawRectangle(rect.x, rect.y, rect.width, rect.height, fillColor);
  if (states[0]) DrawRectangle(rect.x, rect.y + wallThickness, wallThickness, rect.height - 2 * wallThickness, outlineColor);

  if (states[1]) DrawRectangle(rect.x + wallThickness, rect.y, rect.width - 2 * wallThickness, wallThickness, outlineColor);

  if (states[2]) DrawRectangle(rect.x + rect.width - wallThickness, rect.y + wallThickness, wallThickness, rect.height - 2 * wallThickness, outlineColor);

  if (states[3]) DrawRectangle(rect.x + wallThickness, rect.y + rect.height - wallThickness, rect.width - 2 * wallThickness, wallThickness, outlineColor);

  if (states[4]) DrawRectangle(rect.x, rect.y, wallThickness, wallThickness, outlineColor);

  if (states[5]) DrawRectangle(rect.x + rect.width - wallThickness, rect.y, wallThickness, wallThickness, outlineColor);

  if (states[6]) DrawRectangle(rect.x, rect.y + rect.height - wallThickness, wallThickness, wallThickness, outlineColor);

  if (states[7]) DrawRectangle(rect.x + rect.width - wallThickness, rect.y + rect.height - wallThickness, wallThickness, wallThickness, outlineColor);

  if (level == nullptr) return;
  for (GameObject* gameObject : level->gameObjects) {
    if (Key* key = dynamic_cast<Key*>(gameObject)) {
      if (keyId == key->keyId && key->collected) {
        open = true;
        isOpening = true;
      }
    }
  }
}

void KeyBlock::updateKeyBlock(std::vector<KeyBlock*> keyBlocks) {
  for (int i = 0; i < 8; i++) {
    states[i] = true;
  }

  bool d1 = false;
  bool d2 = false;
  bool d3 = false;
  bool d4 = false;

  for (KeyBlock* keyBlock : keyBlocks) {
    if (keyBlock->rect.x + 40 == rect.x && keyBlock->rect.y == rect.y) states[0] = false;
    if (keyBlock->rect.x - 40 == rect.x && keyBlock->rect.y == rect.y) states[2] = false;
    if (keyBlock->rect.x == rect.x && keyBlock->rect.y + 40 == rect.y) states[1] = false;
    if (keyBlock->rect.x == rect.x && keyBlock->rect.y - 40 == rect.y) states[3] = false;

    if (keyBlock->rect.x - 40 == rect.x && keyBlock->rect.y - 40 == rect.y) d1 = true;
    if (keyBlock->rect.x + 40 == rect.x && keyBlock->rect.y - 40 == rect.y) d2 = true;
    if (keyBlock->rect.x - 40 == rect.x && keyBlock->rect.y + 40 == rect.y) d3 = true;
    if (keyBlock->rect.x + 40 == rect.x && keyBlock->rect.y + 40 == rect.y) d4 = true;
  }

  if (d1 && !states[2] && !states[3]) states[7] = false;
  if (d2 && !states[0] && !states[3]) states[6] = false;
  if (d3 && !states[1] && !states[2]) states[5] = false;
  if (d4 && !states[0] && !states[1]) states[4] = false;
}

KeyBlock* KeyBlock::clone() {
  KeyBlock* clone = new KeyBlock({rect.x, rect.y}, keyId, level, zLayer);
  clone->rect = rect;
  clone->paths = paths;
  return clone;
}
