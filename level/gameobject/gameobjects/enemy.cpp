#include "enemy.hpp"

void Enemy::tick(Player* player) {
  GameObject::tick(player);
  DrawTextureEx(enemyTexture, {rect.x, rect.y}, 0.0f, (2.0f / enemyTexture.width) * radius, WHITE);
}
