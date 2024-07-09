#include <raylib.h>
#include "level/level.hpp"
#include "utils/constants.hpp"
#include "utils/fonts.hpp"
#include "utils/needed.hpp"
#include "utils/sounds.hpp"
#include "utils/textures.hpp"

int main() {
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  SetConfigFlags(FLAG_VSYNC_HINT);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The World's Hardest Game: Reloaded");
  InitAudioDevice();

  loadSounds();
  loadFonts();
  loadTextures();

  SetTargetFPS(240);

  while(true) {
    BeginDrawing();

    switch(TWHGReloaded::state) {
      case MENU:
        break;
      case EDITOR:
        TWHGReloaded::editor.tick();
        break;
      case PLAYING:
        TWHGReloaded::level.tick();
        break;
      case PLAYTEST:
        TWHGReloaded::editor.level->tick();
        if (IsKeyReleased(KEY_ESCAPE)) {
          TWHGReloaded::state = EDITOR;
          TWHGReloaded::editor.level->reset();
        }
        break;
    }

    EndDrawing();
  }

  CloseAudioDevice();
  CloseWindow();

  return 0;
}

