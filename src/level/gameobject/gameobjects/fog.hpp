#ifndef FOG_HPP
#define FOG_HPP

#include <raylib.h>
#include "../gameobject.hpp"

class FogBlock : public GameObject {
public:

  bool visible = true;
  int radius = 100;

  void tick(Player* player) override;

  FogBlock(Vector2 pos, Level* level, int zLayer) : GameObject(Rectangle{pos.x, pos.y, 40.0f, 40.0f}, false, level, zLayer) {
    typeId = 9;
  };

  FogBlock* clone() override;
  
  void serialize(std::ofstream& ofs) const override {
    GameObject::serialize(ofs);
    
    ofs.write((char*)&visible, sizeof(visible));    
    ofs.write((char*)&radius, sizeof(radius));
  }
  
  void deserialize(std::ifstream& ifs) override {
    GameObject::deserialize(ifs);

    ifs.read((char*)&visible, sizeof(visible));
    ifs.read((char*)&radius, sizeof(radius));
  }
};

#endif
