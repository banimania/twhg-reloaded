#include "enemy.hpp"
#include <raylib.h>

void Enemy::tick(Player player) {
  DrawCircle(rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f, rect.width / 2.0f, outlineColor);
  DrawCircle(rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f, rect.width / 3.0f, fillColor);
}
