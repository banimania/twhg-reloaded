#include "player.hpp"

void Player::tick() {
  
  float dx, dy;

  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) dy -= speed * GetFrameTime();
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) dy += speed * GetFrameTime();
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) dx -= speed * GetFrameTime();
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) dx += speed * GetFrameTime();

  x += dx;
  y += dy;

  DrawRectangle(x, y, size, size, outlineColor);
  DrawRectangle(x + (size / 6.0f), y + (size / 6.0f), (2.0f * size / 3.0f), (2.0f * size / 3.0f), fillColor);
}
