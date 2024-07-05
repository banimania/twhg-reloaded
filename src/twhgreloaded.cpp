#include <raylib.h>
#include "level/gameobject/gameobjects/conveyor.hpp"
#include "level/gameobject/gameobjects/key.hpp"
#include "level/gameobject/gameobjects/keyblock.hpp"
#include "level/gameobject/gameobjects/wallblock.hpp"
#include "level/gameobject/gameobjects/enemy.hpp"
#include "level/gameobject/gameobjects/coin.hpp"
#include "level/gameobject/gameobjects/checkpoint.hpp"
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
  Conveyor* conveyor = new Conveyor({200, 240}, UP, &TWHGReloaded::level);
  Conveyor* conveyor2 = new Conveyor({240, 240}, RIGHT, &TWHGReloaded::level);
  Coin* coin = new Coin({500, 500}, 10.0f, &TWHGReloaded::level);
  Key* key = new Key({180, 140}, 1, &TWHGReloaded::level);
  KeyBlock* keyBlock = new KeyBlock({120, 120}, 1, &TWHGReloaded::level);
  Checkpoint* checkpoint = new Checkpoint({200, 120}, &TWHGReloaded::level);
  TWHGReloaded::level.gameObjects.push_back(testWall);
  TWHGReloaded::level.gameObjects.push_back(enemy);
  TWHGReloaded::level.gameObjects.push_back(conveyor);
  TWHGReloaded::level.gameObjects.push_back(conveyor2);
  TWHGReloaded::level.gameObjects.push_back(coin);
  TWHGReloaded::level.gameObjects.push_back(key);
  TWHGReloaded::level.gameObjects.push_back(keyBlock);
  TWHGReloaded::level.gameObjects.push_back(checkpoint);
  
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

