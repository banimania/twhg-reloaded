#include "level.hpp"
#include <raylib.h>

void Level::tick() {
  BeginMode2D(camera);

  background.tick();
  player.tick();

  EndMode2D();
}
