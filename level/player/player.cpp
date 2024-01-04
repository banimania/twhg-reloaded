#include "player.hpp"
#include "../level.hpp"
#include "../gameobject/gameobjects/enemy.hpp"
#include "../../utils/sounds.hpp"
#include <raylib.h>

void Player::tick(Level* level) {
  float dx = 0.0f, dy = 0.0f;

  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) dy -= speed * GetFrameTime();
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) dy += speed * GetFrameTime();
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) dx -= speed * GetFrameTime();
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) dx += speed * GetFrameTime();

  float nx = rect.x;
  float ny = rect.y;
  if (!isDying) {
    nx += dx;
    ny += dy;
  } else {
    dyingTimer += GetFrameTime();
    if (dyingTimer > dyingTime) {
      isDying = false;
      dyingTimer = 0.0f;
      rect.x = level->startX;
      rect.y = level->startY;
    }
  }

  if (nx != rect.x || ny != rect.y) {
    bool xCol = false, yCol = false;

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

  for (GameObject* gameObject : level->gameObjects) {
    if (Enemy* enemy = dynamic_cast<Enemy*>(gameObject)) {
      if (CheckCollisionCircleRec({enemy->rect.x + enemy->rect.width / 2.0f, enemy->rect.y + enemy->rect.height / 2.0f}, enemy->radius / 2.0f, rect)) {
        if (!isDying) die();
      }
    }
  }

  if (isDying) {
    float alpha = (1 - dyingTimer / dyingTime) * 255.0f;
    DrawRectangle(rect.x, rect.y, rect.width, rect.height / 6.0f, {outlineColor.r, outlineColor.g, outlineColor.b, static_cast<unsigned char>(alpha)});
    DrawRectangle(rect.x, rect.y + (rect.width / 6.0f), rect.width / 6.0f, rect.height * (5.0f / 6.0f), {outlineColor.r, outlineColor.g, outlineColor.b, static_cast<unsigned char>(alpha)});
    DrawRectangle(rect.x + rect.width * (5.0f / 6.0f), rect.y + (rect.width / 6.0f), rect.width / 6.0f, rect.height * (5.0f / 6.0f), {outlineColor.r, outlineColor.g, outlineColor.b, static_cast<unsigned char>(alpha)});
    DrawRectangle(rect.x + (rect.width / 6.0f), rect.y + rect.height * (5.0f / 6.0f), rect.width - (2.0f * rect.width / 6.0f), rect.height / 6.0f, {outlineColor.r, outlineColor.g, outlineColor.b, static_cast<unsigned char>(alpha)});
    DrawRectangle(rect.x + (rect.width / 6.0f), rect.y + (rect.height / 6.0f), (2.0f * rect.width / 3.0f), (2.0f * rect.height / 3.0f), {fillColor.r, fillColor.g, fillColor.b, static_cast<unsigned char>(alpha)});
    return;
  }

  DrawRectangle(rect.x, rect.y, rect.width, rect.height, outlineColor);
  DrawRectangle(rect.x + (rect.width / 6.0f), rect.y + (rect.height / 6.0f), (2.0f * rect.width / 3.0f), (2.0f * rect.height / 3.0f), fillColor);
}

void Player::die() {
  isDying = true;
  PlaySound(deathSound);
}
