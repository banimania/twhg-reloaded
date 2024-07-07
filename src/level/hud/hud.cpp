#include "hud.hpp"
#include "../level.hpp"
#include "../../utils/fonts.hpp"
#include "../../utils/constants.hpp"
#include <iomanip>
#include <raylib.h>
#include <sstream>
#include <string>

std::string formatTime(float time) {
  int millis = (int) (time * 1000) % 1000;
  int seconds = (int) time % 60;
  int minutes = ((int) time / 60) % 60;
  int hours = ((int) time / 3600);
  
  std::stringstream stream;

  if (hours) stream << std::setw(2) << std::setfill('0') << hours << ":";

  if (minutes) stream << std::setw(2) << std::setfill('0') << minutes << ":";

  stream << std::setw(2) << std::setfill('0') << seconds << "." << std::setw(2) << std::setfill('0') << millis;

  std::string final = stream.str();
  return final;
}

void HUD::tick() {
  int fontSizeBold = 35;
  float spacing = 2.0f;

  DrawRectangle(0, 0, 1280, 80, {0, 0, 0, 255}); 
  DrawTextEx(hudFontBold, "LEVEL", {(SCREEN_WIDTH / 4.0f - MeasureTextEx(hudFontBold, "LEVEL", fontSizeBold, spacing).x), 9}, fontSizeBold, spacing, {255, 255, 255, 255});
  DrawTextEx(hudFont, level->name.c_str(), {(SCREEN_WIDTH / 4.0f - MeasureTextEx(hudFontBold, "LEVEL", fontSizeBold, spacing).x), 38}, fontSizeBold, spacing, {255, 255, 255, 255});
 
  DrawTextEx(hudFontBold, "DEATHS", {(2.0f * SCREEN_WIDTH / 4.0f - MeasureTextEx(hudFontBold, "DEATHS", fontSizeBold, spacing).x), 9}, fontSizeBold, spacing, {255, 255, 255, 255});
  DrawTextEx(hudFont, std::to_string(level->player.deaths).c_str(), {(2.0f * SCREEN_WIDTH / 4.0f - MeasureTextEx(hudFontBold, "DEATHS", fontSizeBold, spacing).x), 38}, fontSizeBold, spacing, {255, 255, 255, 255});
  
  DrawTextEx(hudFontBold, "TIME", {(3.0f * SCREEN_WIDTH / 4.0f - MeasureTextEx(hudFontBold, "TIME", fontSizeBold, spacing).x), 9}, fontSizeBold, spacing, {255, 255, 255, 255});
  DrawTextEx(hudFont, formatTime(level->time).c_str(), {(3.0f * SCREEN_WIDTH / 4.0f - MeasureTextEx(hudFontBold, "TIME", fontSizeBold, spacing).x), 38}, fontSizeBold, spacing, {255, 255, 255, 255});
}

void HUD::tickEditor() {
  int fontSizeBold = 35;
  float spacing = 2.0f;

  DrawRectangle(0, 0, 1280, 80, {0, 0, 0, 255}); 
  DrawTextEx(hudFontBold, "LEVEL", {(SCREEN_WIDTH / 4.0f - MeasureTextEx(hudFontBold, "LEVEL", fontSizeBold, spacing).x), 9}, fontSizeBold, spacing, {255, 255, 255, 255});
  DrawTextEx(hudFont, level->name.c_str(), {(SCREEN_WIDTH / 4.0f - MeasureTextEx(hudFontBold, "LEVEL", fontSizeBold, spacing).x), 38}, fontSizeBold, spacing, {255, 255, 255, 255});
 
  DrawTextEx(hudFontBold, "OBJECTS", {(2.0f * SCREEN_WIDTH / 4.0f - MeasureTextEx(hudFontBold, "OBJECTS", fontSizeBold, spacing).x), 9}, fontSizeBold, spacing, {255, 255, 255, 255});
  DrawTextEx(hudFont, std::to_string(level->gameObjects.size()).c_str(), {(2.0f * SCREEN_WIDTH / 4.0f - MeasureTextEx(hudFontBold, "OBJECTS", fontSizeBold, spacing).x), 38}, fontSizeBold, spacing, {255, 255, 255, 255});
  
  DrawTextEx(hudFontBold, "FPS", {(3.0f * SCREEN_WIDTH / 4.0f - MeasureTextEx(hudFontBold, "FPS", fontSizeBold, spacing).x), 9}, fontSizeBold, spacing, {255, 255, 255, 255});
  DrawTextEx(hudFont, std::to_string(GetFPS()).c_str(), {(3.0f * SCREEN_WIDTH / 4.0f - MeasureTextEx(hudFontBold, "FPS", fontSizeBold, spacing).x), 38}, fontSizeBold, spacing, {255, 255, 255, 255});
}
