#include "player.hpp"
#include "../level.hpp"
#include "../gameobject/gameobjects/enemy.hpp"

#include <iostream>
#include <raylib.h>

void Player::tick(Level* level) {
  float dx = 0.0f, dy = 0.0f;

  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) dy -= speed * GetFrameTime();
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) dy += speed * GetFrameTime();
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) dx -= speed * GetFrameTime();
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) dx += speed * GetFrameTime();

  if (!canDash) dashTimer += GetFrameTime();
  if (dashing && dashTimer >= dashTime) dashing = false;
  if (!dashing && dashTimer >= 4 * dashTime) canDash = true;
  if (IsKeyDown(KEY_Z) && canDash) {
    canDash = false;
    dashing = true;
    dashTimer = 0.0f;
    
    dashX = dx;
    dashY = dy;
  }

  if (dashing) {
    dx = 4 * dashX;
    dy = 4 * dashY;
  }

  float nx = rect.x + dx;
  float ny = rect.y + dy;

  if (nx != rect.x || ny != rect.y) {
    bool xCol, yCol;

    for (GameObject* gameObject : level->gameObjects) {
      if (gameObject->solid) {
        if (CheckCollisionRecs({nx, rect.y, rect.width, rect.height}, gameObject->rect)) xCol = true;
        if (CheckCollisionRecs({rect.x, ny, rect.width, rect.height}, gameObject->rect)) yCol = true;
      }

      if (xCol) {
        if (dx > 0) rect.x = gameObject->rect.x - rect.width;
        else rect.x = gameObject->rect.x + gameObject->rect.width;
      }

      if (yCol) {
        if (dy > 0) rect.y = gameObject->rect.y - rect.height;
        else rect.y = gameObject->rect.y + gameObject->rect.height;
      }

      if (xCol || yCol) break;
    }

    if (!xCol) rect.x += dx;
    if (!yCol) rect.y += dy;
  }

  /*for (GameObject* gameObject : level->gameObjects) {
    if (Enemy* enemy = dynamic_cast<Enemy*>(gameObject)) {
      std::cout << enemy->rect.x << std::endl;
    }
  }*/

  DrawRectangle(rect.x, rect.y, rect.width, rect.height, outlineColor);
  DrawRectangle(rect.x + (rect.width / 6.0f), rect.y + (rect.height / 6.0f), (2.0f * rect.width / 3.0f), (2.0f * rect.height / 3.0f), fillColor);
}
