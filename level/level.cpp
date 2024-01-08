#include "level.hpp"
#include <raylib.h>

void Level::tick() {
  time += GetFrameTime();

  BeginMode2D(camera);

  background.tick();

  for (GameObject* gameObject : gameObjects) {
    gameObject->tick(&player);
  }

  player.tick(this);

  EndMode2D();

  hud.tick();
}
