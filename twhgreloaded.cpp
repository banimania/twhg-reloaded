#include <raylib.h>
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

  Path* testPath = new Path();
  testPath->instructions.push_back(new WaitInstruction(1));
  testPath->instructions.push_back(new CircularInstruction({40, 40}, 200, 360));
  testPath->instructions.push_back(new WaitInstruction(1));
  testPath->instructions.push_back(new LinealInstruction({40, 0}, {560, 560}));
  testPath->instructions.push_back(new LinealInstruction({0, 40}, {560, 560}));
  testPath->instructions.push_back(new LinealInstruction({-40, 0}, {560, 560}));
  testPath->instructions.push_back(new LinealInstruction({0, -40}, {560, 560}));
  WallBlock* testWall = new WallBlock({200, 200}, &TWHGReloaded::level);
  testWall->paths.push_back(testPath);
  Enemy* enemy = new Enemy({300, 300}, 10.0f, &TWHGReloaded::level);
  enemy->paths.push_back(testPath);
  TWHGReloaded::level.gameObjects.push_back(testWall);
  TWHGReloaded::level.gameObjects.push_back(enemy);
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

