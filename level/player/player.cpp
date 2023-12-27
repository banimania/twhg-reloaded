#include "player.hpp"
#include <raylib.h>

void Player::tick() {
  DrawRectangle(x, y, size, size, outlineColor);
  DrawRectangle(x + (size / 6.0f), y + (size / 6.0f), (2.0f * size / 3.0f), (2.0f * size / 3.0f), fillColor);
}
