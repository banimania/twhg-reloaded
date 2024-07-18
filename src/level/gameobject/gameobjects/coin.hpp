#ifndef COIN_HPP
#define COIN_HPP

#include <raylib.h>
#include "../gameobject.hpp"
#include "../../../utils/textures.hpp"
#include "../../../utils/sounds.hpp"

class Coin : public GameObject {
public:
  Color outlineColor = coinColorOutline;
  Color fillColor = coinColorFill;
  
  float radius;

  bool saved = false;

  bool collected = false;
  bool isBeingCollected = false;
  float collectTimer = 0.0f, collectTime = 0.4f;

  void tick(Player* player) override;

  Coin(Vector2 pos, float radius, Level* level, int zLayer) : GameObject(Rectangle{pos.x - 10.0f, pos.y - 10.0f, 2.0f * radius, 2.0f * radius}, false, level, zLayer), radius(radius) {
    typeId = 4;
  };
  
  bool operator==(const Coin& other) const {
    return (radius == other.radius && outlineColor.r == other.outlineColor.r && outlineColor.g == other.outlineColor.g && outlineColor.b == other.outlineColor.b && outlineColor.a == other.outlineColor.a && fillColor.r == other.fillColor.r && fillColor.g == other.fillColor.g && fillColor.b == other.fillColor.b && fillColor.a == other.fillColor.a);
  }
  
  bool equals(const GameObject& other) const override {
    if (const Coin* o = dynamic_cast<const Coin*>(&other)) {
      return *this == *o;
    }
    return false;
  }

  Coin* clone() override;
  
  void serialize(std::ofstream& ofs) const override {
    GameObject::serialize(ofs);
    
    ofs.write((char*)&outlineColor, sizeof(outlineColor));
    ofs.write((char*)&fillColor, sizeof(fillColor));
    ofs.write((char*)&radius, sizeof(radius));
  }
  
  void deserialize(std::ifstream& ifs) override {
    GameObject::deserialize(ifs);

    ifs.read((char*)&outlineColor, sizeof(outlineColor));
    ifs.read((char*)&fillColor, sizeof(fillColor));
    ifs.read((char*)&radius, sizeof(radius));
  }
};

#endif
