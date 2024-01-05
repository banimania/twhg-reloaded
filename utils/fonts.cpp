#include "fonts.hpp"
#include <raylib.h>

void loadFonts() {
  hudFont = LoadFont("./res/fonts/arial.ttf");
  hudFontBold = LoadFont("./res/fonts/arial_bold.ttf");
}
