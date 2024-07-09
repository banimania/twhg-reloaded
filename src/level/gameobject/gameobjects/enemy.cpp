#include "enemy.hpp"
#include <raylib.h>

void Enemy::tick(Player* player) {
  GameObject::tick(player);
  DrawCircle(rect.x + 10, rect.y + 10, 10.0f, outlineColor);
  DrawCircle(rect.x + 10, rect.y + 10, 6.0f, fillColor);
  //DrawTextureEx(enemyTexture, {rect.x, rect.y}, 0.0f, (2.0f / enemyTexture.width) * radius, WHITE);

  //Check collision
  if (CheckCollisionCircleRec({rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f}, radius / 2.0f, player->rect)) {
    if (!player->isDying) player->die();
  }

}

Enemy* Enemy::clone() {
  Enemy* clone = new Enemy({rect.x, rect.y}, 10.0f, level, zLayer);
  clone->rect = rect;
  clone->paths = paths;
  return clone;
}
