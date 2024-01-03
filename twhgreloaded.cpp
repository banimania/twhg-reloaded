#include <raylib.h>
#include "level/gameobject/gameobjects/enemy.hpp"
#include "level/gameobject/gameobjects/wallblock.hpp"
#include "level/level.hpp"
#include "utils/constants.hpp"
#include "utils/needed.hpp"

int main() {
  SetConfigFlags(FLAG_MSAA_4X_HINT);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The World's Hardest Game: Reloaded");
  InitAudioDevice();

  SetTargetFPS(60);

  TWHGReloaded::level.gameObjects.push_back(new WallBlock({200, 200}));
  TWHGReloaded::level.gameObjects.push_back(new Enemy({380, 380}, 10.0f));
  while(!WindowShouldClose()) {
    BeginDrawing();

    switch(TWHGReloaded::state) {
      case MENU:
        break;
      case EDITOR:
        break;
      case PLAYING:
        TWHGReloaded::level.tick();
        break;
    }

    EndDrawing();
  }

  CloseAudioDevice();
  CloseWindow();

  return 0;
}

