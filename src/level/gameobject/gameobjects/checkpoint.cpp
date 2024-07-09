#include "checkpoint.hpp"
#include <raylib.h>
#include "../../level.hpp"
#include "coin.hpp"
#include "key.hpp"
#include "keyblock.hpp"

void Checkpoint::tick(Player* player) {
  GameObject::tick(player);
  DrawRectangleRec(rect, fillColor);

  if (CheckCollisionRecs(player->rect, rect)) {
    player->lastCheckpoint = {player->rect.x, player->rect.y};
    for (GameObject* gameObject : level->gameObjects) {
      if (Coin* coin = dynamic_cast<Coin*>(gameObject)) {
        if (coin->collected) coin->saved = true;
      } else if (Key* key = dynamic_cast<Key*>(gameObject)) {
        if (key->collected) key->saved = true;
      } else if (KeyBlock* keyBlock = dynamic_cast<KeyBlock*>(gameObject)) {
        if (keyBlock->open) keyBlock->saved = true;
      }
    }
  }
}

Checkpoint* Checkpoint::clone() {
  Checkpoint* clone = new Checkpoint({rect.x, rect.y}, goal, level, zLayer);
  clone->rect = rect;
  clone->paths = paths;
  return clone;
}
