#include "level.hpp"
#include "gameobject/gameobjects/checkpoint.hpp"
#include "gameobject/gameobjects/conveyor.hpp"
#include "gameobject/gameobjects/key.hpp"
#include "gameobject/gameobjects/keyblock.hpp"
#include "gameobject/gameobjects/coin.hpp"
#include "../utils/shaders.hpp"
#include <raylib.h>

void Level::tick() {
  if (freeCameraMode) {
    //Vector2 centerWorld = GetScreenToWorld2D({SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f}, camera);
    Vector2 target = {player.rect.x + player.rect.width / 2.0f - SCREEN_WIDTH / 2.0f, player.rect.y + player.rect.height / 2.0f - SCREEN_HEIGHT / 2.0f};
    camera.target = target;
    /*Vector2 move = {target.x - camera.target.x, target.y - camera.target.y};
    camera.target.x += std::clamp(move.x, -player.speed / 240, player.speed / 240);
    camera.target.y += std::clamp(move.y, -player.speed / 240, player.speed / 240);*/
  } else {
    if (player.rect.x + player.rect.width / 2.0f > camGoalX + SCREEN_WIDTH) {
      camGoalX += SCREEN_WIDTH;
    } else if (player.rect.x + player.rect.width / 2.0f < camGoalX) {
      camGoalX -= SCREEN_WIDTH;
    }

    if (std::abs(camGoalX - camera.target.x) <= GetFrameTime() * camMoveSpeed) camera.target.x = camGoalX;
    if (camera.target.x > camGoalX) camera.target.x -= GetFrameTime() * camMoveSpeed;
    else if (camera.target.x < camGoalX) camera.target.x += GetFrameTime() * camMoveSpeed;
    
    if (player.rect.y + player.rect.height / 2.0f > camGoalY + SCREEN_HEIGHT) {
      camGoalY += SCREEN_HEIGHT - 80;
    } else if (player.rect.y + player.rect.height / 2.0f < camGoalY + 80) {
      camGoalY -= SCREEN_HEIGHT - 80;
    }

    if (std::abs(camGoalY - camera.target.y) <= GetFrameTime() * camMoveSpeed) camera.target.y = camGoalY;
    if (camera.target.y > camGoalY) camera.target.y -= GetFrameTime() * camMoveSpeed;
    else if (camera.target.y < camGoalY) camera.target.y += GetFrameTime() * camMoveSpeed;
  }

  time += GetFrameTime();

  BeginMode2D(camera);

  background.tick(camera);

  tickConveyorManager();

  bool setAnimationCheckpoint = true;
  for (Checkpoint* checkpoint : getGameObjects<Checkpoint>()) {
    if (CheckCollisionRecs(player.rect, checkpoint->rect)) {
      setAnimationCheckpoint = false;
      break;
    }
  }
  if (setAnimationCheckpoint) {
    for (Checkpoint* checkpoint : getGameObjects<Checkpoint>()) {
      checkpoint->shouldAnimate = true;
    }
  }

  std::vector<Path*> pathsTicked;
  for (int i = 0; i < gameObjects.size(); i++) {
    //for (GameObject* gameObject : gameObjects) {
    GameObject* gameObject = gameObjects[i];
    for (Path* path : gameObject->paths) {
      if (std::find(pathsTicked.begin(), pathsTicked.end(), path) == pathsTicked.end()) {
        path->tick();
        pathsTicked.push_back(path);
      }
    }

    gameObject->tick(&player);
   
    //last vector reset in order to fix inaccuracies (circle movement moment)
    for (Path* path : pathsTicked) {
      if (i == gameObjects.size() - 1) path->getCurrentInstruction()->last = {0.0f, 0.0f};
    }
  }

  player.tick(this);

  EndMode2D();

  if (player.fogRadius != player.fogStarterRadius) {
    Vector2 fogCenterVector = GetWorldToScreen2D({player.rect.x + player.rect.width / 2.0f, player.rect.y + player.rect.height / 2.0f}, camera);
    fogCenterVector.y = SCREEN_HEIGHT - fogCenterVector.y;
    SetShaderValue(fogShader, GetShaderLocation(fogShader, "fogCenter"), &fogCenterVector, SHADER_UNIFORM_VEC2);
    SetShaderValue(fogShader, GetShaderLocation(fogShader, "fogRadius"), &(player.fogRadius), SHADER_UNIFORM_FLOAT);
    BeginShaderMode(fogShader);
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
    EndShaderMode();
  }

  hud.tick();
}

void Level::death() {
  player.rect.x = player.lastCheckpoint.x;
  player.rect.y = player.lastCheckpoint.y;

  player.deaths++;

  camera = {{0, 0}, {0, 0}, 0.0f, 1.0f};
  if (freeCameraMode) {
    camera.target = {player.rect.x + player.rect.width / 2.0f - SCREEN_WIDTH / 2.0f, player.rect.y + player.rect.height / 2.0f - SCREEN_HEIGHT / 2.0f};
  }

  for (GameObject* gameObject : gameObjects) {
    if (Key* keyObject = dynamic_cast<Key*>(gameObject)) {
      if (keyObject->saved) continue;

      keyObject->collected = false;
      keyObject->isBeingCollected = false;
    } else if (KeyBlock* keyBlock = dynamic_cast<KeyBlock*>(gameObject)) {
      if (keyBlock->saved) continue;

      keyBlock->open = false;
      keyBlock->isOpening = false;
    } else if (Coin* coin = dynamic_cast<Coin*>(gameObject)) {
      if (coin->saved) continue;

      coin->collected = false;
      coin->isBeingCollected = false;
    }
  }
}

void Level::reset() {

  death();

  player.rect.x = startX;
  player.rect.y = startY;
  player.lastCheckpoint = {startX, startY};
  player.isDying = false;

  time = 0;
  player.deaths = 0;
  for (GameObject* gameObject : gameObjects) {
    gameObject->rect = gameObject->originalRect;
    for (Path* path : gameObject->paths) {
      for (Instruction* instruction : path->instructions) {
        path->getCurrentInstruction()->reset();
      }
      path->currentInstructionId = 0;
    }

    if (Key* keyObject = dynamic_cast<Key*>(gameObject)) {
      keyObject->collected = false;
      keyObject->isBeingCollected = false;
    } else if (KeyBlock* keyBlock = dynamic_cast<KeyBlock*>(gameObject)) {
      keyBlock->open = false;
      keyBlock->isOpening = false;
    } else if (Coin* coin = dynamic_cast<Coin*>(gameObject)) {
      coin->collected = false;
      coin->isBeingCollected = false;
    }
  }
}

Rectangle Level::getObjectRectangle(std::vector<GameObject*> objects) {
  float x = 999999, y = 999999, x2 = -999999, y2 = -999999;

  for (GameObject* object : objects) {
    if (object->rect.x < x) x = object->rect.x;
    if (object->rect.y < y) y = object->rect.y;
    if (object->rect.x + object->rect.width > x2) x2 = object->rect.x + object->rect.width;
    if (object->rect.y + object->rect.height > y2) y2 = object->rect.y + object->rect.height;
  }

  return {x, y, x2 - x, y2 - y};
}
