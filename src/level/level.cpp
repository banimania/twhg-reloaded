#include "level.hpp"
#include "gameobject/gameobjects/conveyor.hpp"
#include "gameobject/gameobjects/key.hpp"
#include "gameobject/gameobjects/keyblock.hpp"
#include "gameobject/gameobjects/coin.hpp"
#include <algorithm>
#include <cstdlib>
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
