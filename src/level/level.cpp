#include "level.hpp"

void Level::tick() {
  time += GetFrameTime();

  BeginMode2D(camera);

  background.tick();

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
