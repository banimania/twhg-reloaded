#include "level.hpp"
#include <raylib.h>

void Level::tick() {
  background.tick();
  player.tick();
}
