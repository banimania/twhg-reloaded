#include "hud.hpp"
#include "../level.hpp"
#include "../../utils/fonts.hpp"
#include "../../utils/constants.hpp"
#include <iostream>
#include <raylib.h>

std::string formatTime(float time) {
  int millis = time * 1000;
  std::string final = std::to_string(millis);
  return final;
}

void HUD::tick() {
  int fontSizeBold = 35;
  float spacing = 2.0f;

  DrawRectangle(0, 0, 1280, 80, {0, 0, 0, 255}); 
  DrawTextEx(hudFontBold, "NAME", {(SCREEN_WIDTH / 4.0f - MeasureTextEx(hudFontBold, "NAME", fontSizeBold, spacing).x), 9}, fontSizeBold, spacing, {255, 255, 255, 255});
  DrawTextEx(hudFont, level->name.c_str(), {(SCREEN_WIDTH / 4.0f - MeasureTextEx(hudFontBold, "NAME", fontSizeBold, spacing).x), 38}, fontSizeBold, spacing, {255, 255, 255, 255});
  
  DrawTextEx(hudFontBold, "TIME", {(2.0f * SCREEN_WIDTH / 4.0f - MeasureTextEx(hudFontBold, "TIME", fontSizeBold, spacing).x), 9}, fontSizeBold, spacing, {255, 255, 255, 255});
  DrawTextEx(hudFont, formatTime(level->time).c_str(), {(2.0f * SCREEN_WIDTH / 4.0f - MeasureTextEx(hudFontBold, "TIME", fontSizeBold, spacing).x), 38}, fontSizeBold, spacing, {255, 255, 255, 255});
}
