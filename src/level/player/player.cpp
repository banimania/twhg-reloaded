#include "player.hpp"
#include "../level.hpp"
#include "../gameobject/gameobjects/fog.hpp"
#include <raylib.h>

void Player::tick(Level* level) {

  inFog = false;
  for (GameObject* gameObject : level->gameObjects) {
    if (FogBlock* fogBlock = dynamic_cast<FogBlock*>(gameObject)) {
      if (CheckCollisionRecs(rect, fogBlock->rect)) {
        inFog = true;
        fogFinalRadius = fogBlock->radius;
        break;
      }
    }
  }

  float fogSpeed = GetFrameTime() * 2000;
  if (inFog) {
    if (fogRadius > fogFinalRadius) {
      fogRadius -= fogSpeed;
    } else if (fogRadius < fogFinalRadius) fogRadius = fogFinalRadius;
  } else {
    if (fogRadius < fogStarterRadius) {
      fogRadius += fogSpeed;
    } else if (fogRadius > fogStarterRadius) fogRadius = fogStarterRadius;
  }

  float dx = 0.0f, dy = 0.0f;

  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) dy -= speed * GetFrameTime();
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) dy += speed * GetFrameTime();
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) dx -= speed * GetFrameTime();
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) dx += speed * GetFrameTime();

  float nx = rect.x;
  float ny = rect.y;
  if (!isDying) {
    nx += dx + force.x;
    ny += dy + force.y;
  } else {
    dyingTimer += GetFrameTime();
    if (dyingTimer > dyingTime) {
      isDying = false;
      dyingTimer = 0.0f;
      level->death();
    }
  }

  if (!isDying) {
    bool xCol = false, yCol = false;

    if (dx != 0.0f || force.x != 0.0f) {
      nx = rect.x + dx + force.x;
      for (GameObject* gameObject : level->gameObjects) {
        if (gameObject->solid) {
          if (CheckCollisionRecs({nx, rect.y, rect.width, rect.height}, gameObject->rect)) {
            xCol = true;
            if (rect.x < gameObject->rect.x) rect.x = gameObject->rect.x - rect.width;
            else rect.x = gameObject->rect.x + gameObject->rect.width;
            break;
          }
        }
      }
      if (!xCol) rect.x = nx;
    }

    if (dy != 0.0f || force.y != 0.0f) {
      ny = rect.y + dy + force.y;
      for (GameObject* gameObject : level->gameObjects) {
        if (gameObject->solid) {
          if (CheckCollisionRecs({rect.x, ny, rect.width, rect.height}, gameObject->rect)) {
            yCol = true;
            if (rect.y < gameObject->rect.y) rect.y = gameObject->rect.y - rect.height;
            else rect.y = gameObject->rect.y + gameObject->rect.height;
            break;
          }
        }
      }
      if (!yCol) rect.y = ny;
    }
  }

  force = {0, 0};

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
