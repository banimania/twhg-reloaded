#include "coin.hpp"
#include <raylib.h>

void Coin::tick(Player* player) {

  if (isBeingCollected) {
    DrawTextureEx(coinTexture, {rect.x, rect.y}, 0.0f, (2.0f / coinTexture.width) * radius, {255, 255, 255, (static_cast<unsigned char>((1 - collectTimer / collectTime) * 255.0f))});
    collectTimer += GetFrameTime();
    if (collectTimer > collectTime) {
      isBeingCollected = false;
      collectTimer = 0.0f;
    }
  }

  if (collected) return;

  GameObject::tick(player);
  DrawTextureEx(coinTexture, {rect.x, rect.y}, 0.0f, (2.0f / coinTexture.width) * radius, WHITE);

  //Check collision
  if (CheckCollisionCircleRec({rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f}, radius / 2.0f, player->rect)) {
    PlaySound(coinPickupSound);
    collected = true;
    isBeingCollected = true;
  }

}

Coin* Coin::clone() {
  Coin* clone = new Coin({rect.x, rect.y}, 10.0f, level, zLayer);
  clone->rect = rect;
  clone->paths = paths;
  return clone;
}
