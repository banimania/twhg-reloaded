#include "fonts.hpp"
#include <cstddef>
#include <raylib.h>

void loadFonts() {
  hudFont = LoadFontEx("./res/fonts/arial.ttf", 35, NULL, 0);
  hudFontBold = LoadFontEx("./res/fonts/arial_bold.ttf", 35, NULL, 0);
}
