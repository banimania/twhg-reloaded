#include "level.hpp"
#include "gameobject/gameobjects/conveyor.hpp"
#include "gameobject/gameobjects/key.hpp"
#include "gameobject/gameobjects/keyblock.hpp"
#include "gameobject/gameobjects/coin.hpp"
#include <raylib.h>

void Level::tick() {
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
