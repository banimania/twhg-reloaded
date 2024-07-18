#ifndef BACKGROUNDBLOCK_HPP
#define BACKGROUNDBLOCK_HPP

#include <raylib.h>
#include "../gameobject.hpp"
#include "../../../utils/colors.hpp"

class BackgroundBlock : public GameObject {
public:
  Color fillColor = wallBlockColorFill;

  void tick(Player* player) override;

  BackgroundBlock(Vector2 pos, Level* level, int zLayer) : GameObject(Rectangle{pos.x, pos.y, 40.0f, 40.0f}, false, level, zLayer) {
    typeId = 2;
  };
  
  bool operator==(const BackgroundBlock& other) const {
    return (fillColor.r == other.fillColor.r && fillColor.g == other.fillColor.g && fillColor.b == other.fillColor.b && fillColor.a == other.fillColor.a);
  }
  
  bool equals(const GameObject& other) const override {
    if (const BackgroundBlock* o = dynamic_cast<const BackgroundBlock*>(&other)) {
      return *this == *o;
    }
    return false;
  }

  BackgroundBlock* clone() override;
  
  void serialize(std::ofstream& ofs) const override {
    GameObject::serialize(ofs);
    
    ofs.write((char*)&fillColor, sizeof(fillColor));    
  }
  
  void deserialize(std::ifstream& ifs) override {
    GameObject::deserialize(ifs);

    ifs.read((char*)&fillColor, sizeof(fillColor));
  }
};

#endif
