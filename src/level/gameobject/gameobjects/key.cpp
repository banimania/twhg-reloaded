#include "key.hpp"
#include <algorithm>
#include <map>
#include <raylib.h>
#include <utility>

void Key::tick(Player* player) {
  GameObject::tick(player);

  texture = getKeyTexture(std::make_pair(outlineColor, fillColor));
  if (isBeingCollected) {
    DrawTextureEx(texture, {rect.x - 5, rect.y - 5}, 0.0f, 0.06f, {255, 255, 255, (static_cast<unsigned char>((1 - collectTimer / collectTime) * 255.0f))});
    collectTimer += GetFrameTime();
    if (collectTimer > collectTime) {
      isBeingCollected = false;
      collectTimer = 0.0f;
    }
  }

  if (collected) return;
  
  GameObject::tick(player);
  DrawTextureEx(texture, {rect.x - 5, rect.y - 5}, 0.0f, 0.06f, WHITE);
  
  //Check collision
  if (CheckCollisionRecs(player->rect, {rect.x - 5, rect.y - 5, rect.width + 5, rect.height + 5})) {
    PlaySound(keyPickupSound);
    collected = true;
    isBeingCollected = true;
  }
}

Key* Key::clone() {
  Key* clone = new Key({rect.x, rect.y}, keyId, level, zLayer);
  clone->rect = rect;
  clone->paths = paths;
  return clone;
}

std::unordered_map<std::pair<Color, Color>, Texture, PairColorHash> keyTextures;

/*void loadKeyTexture(std::pair<Color, Color> colors) {
  Image keyImage = LoadImageFromTexture(keyTexture);
  ImageColorReplace(&keyImage, keyColorOutline, colors.first);
  ImageColorReplace(&keyImage, keyColorFill, colors.second);
  keyTextures.insert(std::make_pair(colors, LoadTextureFromImage(keyImage)));
  UnloadImage(keyImage);
}

Texture getKeyTexture(std::pair<Color, Color> colors) {
  if (std::find(keyTextures.begin(), keyTextures.end(), colors) == keyTextures.end()) {
    loadKeyTexture(colors);
  }

  return std::find(keyTextures.begin(), keyTextures.end(), colors)->second;
}*/


void loadKeyTexture(const std::pair<Color, Color>& colors) {
  Image keyImage = LoadImageFromTexture(keyTexture);
  ImageColorReplace(&keyImage, keyColorOutline, colors.first);
  ImageColorReplace(&keyImage, keyColorFill, colors.second);
  keyTextures[colors] = LoadTextureFromImage(keyImage);
  UnloadImage(keyImage);
}

Texture getKeyTexture(const std::pair<Color, Color>& colors) {
  auto it = keyTextures.find(colors);
  if (it == keyTextures.end()) {
    loadKeyTexture(colors);
    it = keyTextures.find(colors);
  }
  return it->second;
}
