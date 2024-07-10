#include <raylib.h>
#include "level/level.hpp"
#include "utils/constants.hpp"
#include "utils/fonts.hpp"
#include "utils/needed.hpp"
#include "utils/sounds.hpp"
#include "utils/textures.hpp"
#if defined(PLATFORM_WEB)
  #include <emscripten/emscripten.h>
#endif

bool running = true;

void mainLoop() {
  BeginDrawing();

  if (IsKeyPressed(KEY_Q)) {
    running = false;
  }

  if (IsKeyPressed(KEY_F)) {
    ToggleFullscreen();
  }

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

int main() {
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  SetConfigFlags(FLAG_VSYNC_HINT);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The World's Hardest Game: Reloaded");
  InitAudioDevice();

  loadSounds();
  loadFonts();
  loadTextures();


#if defined(__EMSCRIPTEN__)
  emscripten_set_main_loop(mainLoop, 240, 1);
#else

  SetTargetFPS(240);

  while(running) {
    mainLoop();
  }

#endif

  CloseAudioDevice();
  CloseWindow();

  return 0;
}

