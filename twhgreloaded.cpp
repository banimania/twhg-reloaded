#include <raylib.h>
#include "level/gameobject/gameobjects/wallblock.hpp"
#include "level/level.hpp"
#include "utils/constants.hpp"

enum GameState { MENU, EDITOR, PLAYING };

static GameState state = PLAYING;
static Level level = Level(100, 100, Player({100, 100}, 30, 150), Background(CHECKERBOARD, backgroundColorPrimary, backgroundColorSecondary, 40.0f));

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The World's Hardest Game: Reloaded");
  InitAudioDevice();

  SetTargetFPS(60);

  level.gameObjects.push_back(new WallBlock({200, 200}));

  while(!WindowShouldClose()) {
    BeginDrawing();

    switch(state) {
      case MENU:
        break;
      case EDITOR:
        break;
      case PLAYING:
        level.tick();
        break;
    }

    EndDrawing();
  }

  CloseAudioDevice();
  CloseWindow();

  return 0;
}
