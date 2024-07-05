#include "textures.hpp"
#include "colors.hpp"
#include <raylib.h>

void loadTextures() {
  Image i = GenImageColor(1024, 1024, {0, 0, 0, 0});
  ImageDrawCircle(&i, 512, 512, 512, enemyColorOutline);
  ImageDrawCircle(&i, 512, 512, 512 * (2.0f / 3.0f), enemyColorFill);
  enemyTexture = LoadTextureFromImage(i);
  UnloadImage(i);
  GenTextureMipmaps(&enemyTexture);
  SetTextureFilter(enemyTexture, TEXTURE_FILTER_BILINEAR);
}
