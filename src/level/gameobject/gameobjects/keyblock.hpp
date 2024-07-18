#ifndef KEYBLOCK_HPP
#define KEYBLOCK_HPP

#include <raylib.h>
#include "../gameobject.hpp"
#include "../../../utils/colors.hpp"
#include "key.hpp"

class KeyBlock : public GameObject {
public:
  Color outlineColor = keyBlockColorOutline;
  Color fillColor = keyBlockColorFill;

  bool states[8] = {true, true, true, true, true, true, true, true};

  bool saved = false;

  int keyId;
  bool open = false;
  bool isOpening = false;
  float openTimer = 0.0f, openTime = 0.4f;

  int wallThickness = 5;

  void tick(Player* player) override;

  KeyBlock(Vector2 pos, int keyId, Level* level, int zLayer) : GameObject(Rectangle{pos.x, pos.y, 40.0f, 40.0f}, true, level, zLayer), keyId(keyId) {
    typeId = 6;
  };
  
  bool operator==(const KeyBlock& other) const {
    return (keyId == other.keyId && outlineColor.r == other.outlineColor.r && outlineColor.g == other.outlineColor.g && outlineColor.b == other.outlineColor.b && outlineColor.a == other.outlineColor.a && fillColor.r == other.fillColor.r && fillColor.g == other.fillColor.g && fillColor.b == other.fillColor.b && fillColor.a == other.fillColor.a);
  }

  bool equals(const GameObject& other) const override {
    if (const KeyBlock* o = dynamic_cast<const KeyBlock*>(&other)) {
      return *this == *o;
    }
    return false;
  }

  void updateKeyBlock(std::vector<KeyBlock*> keyBlocks);

  KeyBlock* clone() override;
  
  void serialize(std::ofstream& ofs) const override {
    GameObject::serialize(ofs);
    
    ofs.write((char*)&outlineColor, sizeof(outlineColor));    
    ofs.write((char*)&fillColor, sizeof(fillColor));
    ofs.write((char*)&states, sizeof(states));
    ofs.write((char*)&keyId, sizeof(keyId));
  }
  
  void deserialize(std::ifstream& ifs) override {
    GameObject::deserialize(ifs);

    ifs.read((char*)&outlineColor, sizeof(outlineColor));
    ifs.read((char*)&fillColor, sizeof(fillColor));
    ifs.read((char*)&states, sizeof(states));
    ifs.read((char*)&keyId, sizeof(keyId));
  }
};

#endif
