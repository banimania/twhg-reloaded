#include <raylib.h>
#include "level/background/background.hpp"
#include "level/level.hpp"
#include "level/player/player.hpp"
#include "utils/colors.hpp"
#include "utils/constants.hpp"

enum GameState { MENU, EDITOR, PLAYING };

static GameState state = PLAYING;
static Level level = Level(100, 100, Player(100, 100, 30, 30), Background(CHECKERBOARD, backgroundColorPrimary, backgroundColorSecondary, 40.0f));

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The World's Hardest Game: Reloaded");
  InitAudioDevice();

  SetTargetFPS(60);

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
