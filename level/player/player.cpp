#include "player.hpp"

void Player::tick() {
  float dx = 0.0f, dy = 0.0f;

  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) dy -= speed * GetFrameTime();
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) dy += speed * GetFrameTime();
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) dx -= speed * GetFrameTime();
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) dx += speed * GetFrameTime();

  float nx = rect.x + dx;
  float ny = rect.y + dy;

  if (nx != rect.x || ny != rect.y) {
    bool xCol, yCol;

    if (!xCol) rect.x += dx;
    if (!yCol) rect.y += dy;
  }

  DrawRectangle(rect.x, rect.y, rect.width, rect.height, outlineColor);
  DrawRectangle(rect.x + (rect.width / 6.0f), rect.y + (rect.height / 6.0f), (2.0f * rect.width / 3.0f), (2.0f * rect.height / 3.0f), fillColor);
}
