#include "keyblock.hpp"
#include "../../level.hpp"
#include "key.hpp"

void KeyBlock::tick(Player* player) {
  GameObject::tick(player);

  if (isOpening) {
    DrawRectangle(rect.x, rect.y, 5, rect.height, {keyBlockColorOutline.r, keyBlockColorOutline.g, keyBlockColorOutline.b, (static_cast<unsigned char>((1 - openTimer / openTime) * 255.0f))});
    DrawRectangle(rect.x, rect.y, rect.width, 5, {keyBlockColorOutline.r, keyBlockColorOutline.g, keyBlockColorOutline.b, (static_cast<unsigned char>((1 - openTimer / openTime) * 255.0f))});
    DrawRectangle(rect.x + rect.width - 5, rect.y + 5, 5, rect.height - 5, {keyBlockColorOutline.r, keyBlockColorOutline.g, keyBlockColorOutline.b, (static_cast<unsigned char>((1 - openTimer / openTime) * 255.0f))});
    DrawRectangle(rect.x + 5, rect.y + rect.height - 5, rect.width - 10, 5, {keyBlockColorOutline.r, keyBlockColorOutline.g, keyBlockColorOutline.b, (static_cast<unsigned char>((1 - openTimer / openTime) * 255.0f))});
    DrawRectangle(rect.x + 5, rect.y + 5, rect.width - 10, rect.height - 10, {keyBlockColorFill.r, keyBlockColorFill.g, keyBlockColorFill.b, (static_cast<unsigned char>((1 - openTimer / openTime) * 255.0f))});
    openTimer += GetFrameTime();
    if (openTimer > openTime) {
      isOpening = false;
      openTimer = 0.0f;
    }
  }
  if (open) return;

  GameObject::tick(player);
  DrawRectangle(rect.x, rect.y, rect.width, rect.height, keyBlockColorOutline);
  DrawRectangle(rect.x + 5, rect.y + 5, rect.width - 10, rect.height - 10, keyBlockColorFill);

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
