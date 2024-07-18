#ifndef WALLBLOCK_HPP
#define WALLBLOCK_HPP

#include <raylib.h>
#include "../gameobject.hpp"
#include "../../../utils/colors.hpp"

class WallBlock : public GameObject {
public:
  Color outlineColor = wallBlockColorOutline, fillColor = wallBlockColorFill;

  bool states[8] = {true, true, true, true, true, true, true, true};

  int wallThickness = 5;

  void tick(Player* player) override;

  void updateWallBlock(std::vector<WallBlock*> wallBlocks);

  WallBlock* clone() override;

  WallBlock(Vector2 pos, Level* level, int zLayer) : GameObject(Rectangle{pos.x, pos.y, 40.0f, 40.0f}, true, level, zLayer) {
    typeId = 1;
  };

  bool operator==(const WallBlock& other) const {
    return (outlineColor.r == other.outlineColor.r && outlineColor.g == other.outlineColor.g && outlineColor.b == other.outlineColor.b && outlineColor.a == other.outlineColor.a && fillColor.r == other.fillColor.r && fillColor.g == other.fillColor.g && fillColor.b == other.fillColor.b && fillColor.a == other.fillColor.a);
  }
  
  bool equals(const GameObject& other) const override {
    if (const WallBlock* o = dynamic_cast<const WallBlock*>(&other)) {
      return *this == *o;
    }
    return false;
  }
  void serialize(std::ofstream& ofs) const override {
    GameObject::serialize(ofs);
    
    ofs.write((char*)&outlineColor, sizeof(outlineColor));    
    ofs.write((char*)&fillColor, sizeof(fillColor));
    ofs.write((char*)&states, sizeof(states));
  }
  
  void deserialize(std::ifstream& ifs) override {
    GameObject::deserialize(ifs);

    ifs.read((char*)&outlineColor, sizeof(outlineColor));
    ifs.read((char*)&fillColor, sizeof(fillColor));
    ifs.read((char*)&states, sizeof(states));
  }
};

#endif
