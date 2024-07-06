#include "editor.hpp"
#include <iostream>
#include <raylib.h>


void Editor::initWidgets() {
  init = true;
}

void Editor::tick() {
  if (!init) initWidgets();

  if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
    camera.target = {camera.target.x - GetMouseDelta().x, camera.target.y - GetMouseDelta().y};
  }

  float wheel = GetMouseWheelMove();
  if (wheel != 0) {
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

    camera.offset = GetMousePosition();

    camera.target = mouseWorldPos;

    float scaleFactor = 1.0f + (0.25f * fabsf(wheel));
    if (wheel < 0) scaleFactor = 1.0f / scaleFactor;
    camera.zoom = std::clamp(camera.zoom * scaleFactor, 0.7f, 2.0f);
  }

  BeginMode2D(camera);
  
  level->background.tick(camera);
  
  drawGrid();

  EndMode2D();
}

void Editor::drawGrid() {
  int areaWidth = 1280;
  int areaHeight = 640;

  int ni = camera.target.x / areaWidth;
  int nj = camera.target.y / areaHeight;

  for (int i = -2 - abs(ni); i <= 2 + abs(ni); i++) {
    for (int j = -2 - abs(nj); j <= 2 + abs(nj); j++) {
      DrawLineEx({(float) i * areaWidth, (float) j * areaHeight + 80}, {(float) (i + 1) * areaWidth, (float) j * areaHeight + 80}, 5.0f, RED);
      DrawLineEx({(float) i * areaWidth, (float) j * areaHeight + 80}, {(float) i * areaWidth, (float) (j + 1) * areaHeight + 80}, 5.0f, RED);
    }
  }
}
