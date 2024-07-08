#include "textures.hpp"
#include "colors.hpp"
#include <raylib.h>

void loadTextures() {
  Image i = GenImageColor(1024, 1024, {0, 0, 0, 0});
  ImageDrawCircle(&i, 512, 512, 512, enemyColorOutline);
  ImageDrawCircle(&i, 512, 512, 512 * (2.0f / 3.0f), enemyColorFill);
  enemyTexture = LoadTextureFromImage(i);
  GenTextureMipmaps(&enemyTexture);
  SetTextureFilter(enemyTexture, TEXTURE_FILTER_BILINEAR);

  ImageDrawCircle(&i, 512, 512, 512, coinColorOutline);
  ImageDrawCircle(&i, 512, 512, 512 * (2.0f / 3.0f), coinColorFill);
  coinTexture = LoadTextureFromImage(i);
  GenTextureMipmaps(&coinTexture);
  SetTextureFilter(coinTexture, TEXTURE_FILTER_BILINEAR);


  i = LoadImage("./res/img/key.png");
  keyTexture = LoadTexture("./res/img/key.png");
  GenTextureMipmaps(&keyTexture);
  SetTextureFilter(keyTexture, TEXTURE_FILTER_BILINEAR);

  UnloadImage(i);

  arrowLeftTexture = LoadTexture("./res/img/arrow_left.png");
  arrowRightTexture = LoadTexture("./res/img/arrow_right.png");

  configurationTexture = LoadTexture("./res/img/configuration.png");
  playTexture = LoadTexture("./res/img/play.png");
  arrowTexture = LoadTexture("./res/img/arrow.png");
}

Texture GetTextureFromName(std::string textureName) {
  if (textureName == "configurationTexture") return configurationTexture;
  else if (textureName == "playTexture") return playTexture;
}
