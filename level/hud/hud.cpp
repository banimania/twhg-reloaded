#include "hud.hpp"
#include "../level.hpp"
#include "../../utils/fonts.hpp"
#include "../../utils/constants.hpp"
#include <iostream>
#include <raylib.h>

void HUD::tick() {
  int fontSizeBold = 35;
  float spacing = 2.0f;

  DrawRectangle(0, 0, 1280, 80, {0, 0, 0, 255}); 
  DrawTextEx(hudFontBold, "FPS", {(SCREEN_WIDTH / 4.0f - MeasureTextEx(hudFontBold, "FPS", fontSizeBold, spacing).x), 9}, fontSizeBold, spacing, {255, 255, 255, 255});
  DrawTextEx(hudFont, std::to_string(GetFPS()).c_str(), {(SCREEN_WIDTH / 4.0f - MeasureTextEx(hudFontBold, "FPS", fontSizeBold, spacing).x), 38}, fontSizeBold, spacing, {255, 255, 255, 255});
}
