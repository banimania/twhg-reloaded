#include "textures.hpp"
#include "colors.hpp"
#include <raylib.h>

void loadTextures() {
  Image i = LoadImage("./res/img/key.png");
  keyTexture = LoadTexture("./res/img/key.png");
  GenTextureMipmaps(&keyTexture);
  SetTextureFilter(keyTexture, TEXTURE_FILTER_BILINEAR);

  UnloadImage(i);

  arrowLeftTexture = LoadTexture("./res/img/arrow_left.png");
  arrowRightTexture = LoadTexture("./res/img/arrow_right.png");

  configurationTexture = LoadTexture("./res/img/configuration.png");
  playTexture = LoadTexture("./res/img/play.png");
  rightArrowTexture = LoadTexture("./res/img/arrow.png");

  Image arrowIm = LoadImageFromTexture(rightArrowTexture);
  ImageRotateCW(&arrowIm);
  downArrowTexture = LoadTextureFromImage(arrowIm);

  ImageRotateCW(&arrowIm);
  leftArrowTexture = LoadTextureFromImage(arrowIm);

  ImageRotateCW(&arrowIm);
  upArrowTexture = LoadTextureFromImage(arrowIm);

  trashTexture = LoadTexture("./res/img/trash.png");
  
  duplicateTexture = LoadTexture("./res/img/duplicate.png");
}

Texture GetTextureFromName(std::string textureName) {
  if (textureName == "configurationTexture") return configurationTexture;
  else if (textureName == "playTexture") return playTexture;
  else if (textureName == "rightArrowTexture") return rightArrowTexture;
  else if (textureName == "downArrowTexture") return downArrowTexture;
  else if (textureName == "leftArrowTexture") return leftArrowTexture;
  else if (textureName == "upArrowTexture") return upArrowTexture;
  else if (textureName == "trashTexture") return trashTexture;
  else if (textureName == "duplicateTexture") return duplicateTexture;
}
