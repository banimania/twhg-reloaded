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

  bool saved = false;

  void tick(Player* player) override;

  Key(Vector2 pos, int keyId, Level* level, int zLayer) : GameObject(Rectangle{pos.x - 10.0f, pos.y - 10.0f, 20.0f, 20.0f}, false, level, zLayer), keyId(keyId) {
    typeId = 5;
  };
  
  bool operator==(const Key& other) const {
    return (keyId == other.keyId && outlineColor.r == other.outlineColor.r && outlineColor.g == other.outlineColor.g && outlineColor.b == other.outlineColor.b && outlineColor.a == other.outlineColor.a && fillColor.r == other.fillColor.r && fillColor.g == other.fillColor.g && fillColor.b == other.fillColor.b && fillColor.a == other.fillColor.a);
  }

  bool equals(const GameObject& other) const override {
    if (const Key* o = dynamic_cast<const Key*>(&other)) {
      return *this == *o;
    }
    return false;
  }
  Key* clone() override;
  
  void serialize(std::ofstream& ofs) const override {
    GameObject::serialize(ofs);
    
    ofs.write((char*)&outlineColor, sizeof(outlineColor));    
    ofs.write((char*)&fillColor, sizeof(fillColor));
    ofs.write((char*)&keyId, sizeof(keyId));
  }
  
  void deserialize(std::ifstream& ifs) override {
    GameObject::deserialize(ifs);

    ifs.read((char*)&outlineColor, sizeof(outlineColor));
    ifs.read((char*)&fillColor, sizeof(fillColor));
    ifs.read((char*)&keyId, sizeof(keyId));
  }
};

extern std::unordered_map<std::pair<Color, Color>, Texture, PairColorHash> keyTextures;

void loadKeyTexture(const std::pair<Color, Color>& colors);
Texture getKeyTexture(const std::pair<Color, Color>& colors);

#endif
