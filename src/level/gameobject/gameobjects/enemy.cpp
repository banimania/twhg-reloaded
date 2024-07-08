#include "enemy.hpp"

void Enemy::tick(Player* player) {
  GameObject::tick(player);
  DrawTextureEx(enemyTexture, {rect.x, rect.y}, 0.0f, (2.0f / enemyTexture.width) * radius, WHITE);

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
