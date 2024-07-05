#include <raylib.h>
#include "level/gameobject/gameobjects/conveyor.hpp"
#include "level/gameobject/gameobjects/wallblock.hpp"
#include "level/gameobject/gameobjects/enemy.hpp"
#include "level/gameobject/path/instruction/instructions/circularinstruction.hpp"
#include "level/gameobject/path/instruction/instructions/linealinstruction.hpp"
#include "level/gameobject/path/instruction/instructions/waitinstruction.hpp"
#include "level/gameobject/path/path.hpp"
#include "level/level.hpp"
#include "utils/constants.hpp"
#include "utils/fonts.hpp"
#include "utils/needed.hpp"
#include "utils/sounds.hpp"
#include "utils/textures.hpp"

int main() {
  SetConfigFlags(FLAG_MSAA_4X_HINT);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The World's Hardest Game: Reloaded");
  InitAudioDevice();

  loadSounds();
  loadFonts();
  loadTextures();

  SetTargetFPS(60);

  WallBlock* testWall = new WallBlock({200, 200}, &TWHGReloaded::level);
  Enemy* enemy = new Enemy({300, 300}, 10.0f, &TWHGReloaded::level);
  Conveyor* conveyor = new Conveyor({200, 240}, &TWHGReloaded::level);
  Conveyor* conveyor2 = new Conveyor({240, 240}, &TWHGReloaded::level);
  conveyor2->direction = RIGHT;
  TWHGReloaded::level.gameObjects.push_back(testWall);
  TWHGReloaded::level.gameObjects.push_back(enemy);
  TWHGReloaded::level.gameObjects.push_back(conveyor);
  TWHGReloaded::level.gameObjects.push_back(conveyor2);
  
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

