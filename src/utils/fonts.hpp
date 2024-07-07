#ifndef FONTS_HPP
#define FONTS_HPP

#include <raylib.h>

inline Font hudFont;
inline Font hudFontBold;

void DrawOutlinedCenteredText(Font font, const char* text, Rectangle rect, int fontSize, Color color, int outlineSize, Color outlineColor);
void DrawOutlinedText(Font font, const char *text, float posX, float posY, int fontSize, Color color, int outlineSize, Color outlineColor);
void loadFonts();

#endif
