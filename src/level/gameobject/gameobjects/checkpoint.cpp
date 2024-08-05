#include "checkpoint.hpp"
#include "enemy.hpp"
#include "../../level.hpp"
#include <raylib.h>
#include "../../../utils/needed.hpp"

void Checkpoint::tick(Player* player) {
  GameObject::tick(player);

  if (CheckCollisionRecs(player->rect, rect)) {
  
    if (TWHGReloaded::state == PLAYING) {
      if (goal && !level->beat && level->allCoins) {
        level->pause = true;
        level->beat = true;
        level->ss = true;
        return;
      }
    }
    
    std::vector<GameObject*> checkpoints;
    if (shouldAnimate) animation = true;
    checkpoints.push_back(this);
    for (Checkpoint* c : level->getConsecutiveGameObjects<Checkpoint>({rect.x, rect.y})) {
      if (c->shouldAnimate) c->animation = true;
      checkpoints.push_back(c);
    }

    Rectangle rec = level->getObjectRectangle(checkpoints);
    Vector2 centerPoint = {rec.x + rec.width / 2.0f - player->rect.width / 2.0f, rec.y + rec.height / 2.0f - player->rect.height / 2.0f};
    bool center = true;
    
    bool check = false;
  checkSelf:
    if (check) centerPoint = {rect.x + rect.width / 2.0f - player->rect.width / 2.0f, rect.y + rect.height / 2.0f - player->rect.height / 2.0f};
    for (GameObject* gameObject : level->gameObjects) {
      bool isEnemy = false;
      if (Enemy* enemy = dynamic_cast<Enemy*>(gameObject)) isEnemy = true;
      if (isEnemy || gameObject->solid) {
        if (CheckCollisionRecs({centerPoint.x, centerPoint.y, player->rect.width, player->rect.height}, gameObject->rect)) {
          if (!check) {
            check = true;
            goto checkSelf;
          }
          center = false;
          break;
        }

      }
    }
    if (center) player->lastCheckpoint = centerPoint;

    for (GameObject* gameObject : level->gameObjects) {
      if (saveCoins) {
        if (Coin* coin = dynamic_cast<Coin*>(gameObject)) {
          if (coin->collected) coin->saved = true;
        }
      }
      if (saveKeys) {
        if (Key* key = dynamic_cast<Key*>(gameObject)) {
          if (key->collected) key->saved = true;
        } else if (KeyBlock* keyBlock = dynamic_cast<KeyBlock*>(gameObject)) {
          if (keyBlock->open) keyBlock->saved = true;
        }
      }
    }
  }
  
  if (animation) {
    animateTimer += GetFrameTime();

    if (animateTimer > animateTime) {
      animateTimer = 0.0f;
      animation = false;
      shouldAnimate = false;
      goto draw;
    }
    DrawRectangleRec(rect, {static_cast<unsigned char>(fillColor.r * 0.8f + fillColor.r * (0.2f * (animateTimer / animateTime))), static_cast<unsigned char>(fillColor.g * 0.8f + fillColor.g * (0.2f * (animateTimer / animateTime))), static_cast<unsigned char>(fillColor.b * 0.8f + fillColor.b * (0.2f * (animateTimer / animateTime))), fillColor.a});
    return;
  }

draw:

  DrawRectangleRec(rect, fillColor);
}

Checkpoint* Checkpoint::clone() {
  Checkpoint* clone = new Checkpoint({rect.x, rect.y}, goal, level, zLayer);
  clone->rect = rect;
  clone->pathIds = pathIds;
  clone->fillColor = fillColor;
  clone->saveKeys = saveKeys;
  clone->saveCoins = saveCoins;
  clone->goal = goal;
  return clone;
}
