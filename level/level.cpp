#include "level.hpp"

void Level::tick() {
  BeginMode2D(camera);

  background.tick();

  for (GameObject* gameObject : gameObjects) {
    gameObject->tick(player);
  }

  player.tick(this);

  EndMode2D();

  hud.tick();
}
