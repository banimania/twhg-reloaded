#ifndef KEY_HPP
#define KEY_HPP

#include <map>
#include <raylib.h>
#include <unordered_map>
#include "../gameobject.hpp"
#include "../../../utils/textures.hpp"
#include "../../../utils/sounds.hpp"

class Key : public GameObject {
public:
  Color outlineColor = keyColorOutline;
  Color fillColor = keyColorFill;

  Texture texture = keyTexture;

  int keyId;

  bool collected = false;
  bool isBeingCollected = false;
  float collectTimer = 0.0f, collectTime = 0.4f;

  void tick(Player* player) override;

  Key(Vector2 pos, int keyId, Level* level, int zLayer) : GameObject(Rectangle{pos.x - 10.0f, pos.y - 10.0f, 20.0f, 20.0f}, false, level, zLayer), keyId(keyId) {};

  Key* clone() override;
};

extern std::unordered_map<std::pair<Color, Color>, Texture, PairColorHash> keyTextures;

void loadKeyTexture(const std::pair<Color, Color>& colors);
Texture getKeyTexture(const std::pair<Color, Color>& colors);

#endif
