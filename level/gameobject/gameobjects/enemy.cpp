#include "enemy.hpp"

void Enemy::tick(Player player) {
  DrawCircle(rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f, radius, outlineColor);
  DrawCircle(rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f, radius * (2.0f/3.0f), fillColor);
}
