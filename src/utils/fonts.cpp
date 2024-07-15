#include "fonts.hpp"
#include <cstddef>
#include <raylib.h>

void DrawOutlinedCenteredText(Font font, const char* text, Rectangle rect, int fontSize, Color color, int outlineSize, Color outlineColor) {
  float x = rect.x + (rect.width / 2.0f) - MeasureTextEx(font, text, fontSize, 0).x / 2.0f;
  float y = rect.y + (rect.height / 2.0f) - MeasureTextEx(font, text, fontSize, 0).y / 2.0f;

  DrawOutlinedText(font, text, x, y, fontSize, color, outlineSize, outlineColor);
}

void DrawOutlinedText(Font font, const char *text, float posX, float posY, int fontSize, Color color, int outlineSize, Color outlineColor) {
  DrawTextEx(font, text, {posX - outlineSize, posY - outlineSize}, fontSize, 0, outlineColor);
  DrawTextEx(font, text, {posX + outlineSize, posY - outlineSize}, fontSize, 0, outlineColor);
  DrawTextEx(font, text, {posX - outlineSize, posY + outlineSize}, fontSize, 0, outlineColor);
  DrawTextEx(font, text, {posX + outlineSize, posY + outlineSize}, fontSize, 0, outlineColor);
  DrawTextEx(font, text, {posX, posY}, fontSize, 0, color);
}

void loadFonts() {
  hudFont = LoadFontEx("./res/fonts/arial.ttf", 38, NULL, 0);
  SetTextureFilter(hudFont.texture, TEXTURE_FILTER_BILINEAR);
  hudFontBold = LoadFontEx("./res/fonts/arial_bold.ttf", 38, NULL, 0);
  SetTextureFilter(hudFontBold.texture, TEXTURE_FILTER_BILINEAR);
  editorFontBold = LoadFontEx("./res/fonts/arial_bold.ttf", 100, NULL, 0);
  SetTextureFilter(editorFontBold.texture, TEXTURE_FILTER_BILINEAR);
}
