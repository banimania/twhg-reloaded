#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <raylib.h>
#include "../gameobject.hpp"
#include "../../../utils/textures.hpp"

class Enemy : public GameObject {
public:
  Color outlineColor = enemyColorOutline, fillColor = enemyColorFill;

  float radius;

  void tick(Player* player) override;

  Enemy(Vector2 pos, float radius, Level* level, int zLayer) : GameObject(Rectangle{pos.x - 10.0f, pos.y - 10.0f, 2.0f * radius, 2.0f * radius}, false, level, zLayer), radius(radius) {
    typeId = 3;
  };

  Enemy* clone() override;
  
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
