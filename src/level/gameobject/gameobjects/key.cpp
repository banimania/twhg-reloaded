#include "key.hpp"
#include <raylib.h>

void Key::tick(Player* player) {
  GameObject::tick(player);

  if (isBeingCollected) {
    DrawTextureEx(keyTexture, {rect.x - 5, rect.y - 5}, 0.0f, 0.06f, {255, 255, 255, (static_cast<unsigned char>((1 - collectTimer / collectTime) * 255.0f))});
    collectTimer += GetFrameTime();
    if (collectTimer > collectTime) {
      isBeingCollected = false;
      collectTimer = 0.0f;
    }
  }

  if (collected) return;
  
  GameObject::tick(player);
  DrawTextureEx(keyTexture, {rect.x - 5, rect.y - 5}, 0.0f, 0.06f, WHITE);
  
  //Check collision
  if (CheckCollisionRecs(player->rect, {rect.x - 5, rect.y - 5, rect.width + 5, rect.height + 5})) {
    PlaySound(keyPickupSound);
    collected = true;
    isBeingCollected = true;
  }
}
