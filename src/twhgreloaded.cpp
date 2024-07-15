#include <raylib.h>
#include <raymath.h>
#include "level/level.hpp"
#include "utils/constants.hpp"
#include "utils/fonts.hpp"
#include "utils/needed.hpp"
#include "utils/shaders.hpp"
#include "utils/sounds.hpp"
#include "utils/textures.hpp"
#if defined(__EMSCRIPTEN__)
  #include <emscripten/emscripten.h>
#endif

bool running = true;

RenderTexture2D target;

void mainLoop() {
  float scale = std::min((float) GetScreenWidth() / SCREEN_WIDTH, (float) GetScreenHeight() / SCREEN_HEIGHT);

  Vector2 mouse = GetMousePosition();
  TWHGReloaded::mouse.x = (mouse.x - (GetScreenWidth() - (SCREEN_WIDTH * scale)) * 0.5f) / scale;
  TWHGReloaded::mouse.y = (mouse.y - (GetScreenHeight() - (SCREEN_HEIGHT * scale)) * 0.5f) / scale;
  TWHGReloaded::mouse = Vector2Clamp(TWHGReloaded::mouse, (Vector2){ 0, 0 }, (Vector2){ (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT });

  BeginTextureMode(target);

  if (IsKeyPressed(KEY_Q)) {
    running = false;
  }

  if (IsKeyPressed(KEY_F)) {
    int display = GetCurrentMonitor();
    if (IsWindowFullscreen()) {
      SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    } else {
      SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
    }
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

  EndTextureMode();

  BeginDrawing();
  ClearBackground(BLACK);

  DrawTexturePro(target.texture, (Rectangle) {0.0f, 0.0f, (float) target.texture.width, (float)-target.texture.height},
    (Rectangle) {(GetScreenWidth() - ((float) SCREEN_WIDTH * scale)) * 0.5f, (GetScreenHeight() - ((float) SCREEN_HEIGHT * scale)) * 0.5f,
    (float) SCREEN_WIDTH * scale, (float) SCREEN_HEIGHT * scale}, (Vector2) {0, 0}, 0.0f, WHITE);
  EndDrawing();
}

int main() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The World's Hardest Game: Reloaded");
  InitAudioDevice();

  target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
  SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);
  
  loadSounds();
  loadFonts();
  loadTextures();
  loadShaders();

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
