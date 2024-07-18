#ifndef CHECKPOINT_HPP
#define CHECKPOINT_HPP

#include <raylib.h>
#include "../gameobject.hpp"
#include "../../../utils/colors.hpp"
#include "coin.hpp"
#include "key.hpp"
#include "keyblock.hpp"

class Checkpoint : public GameObject {
public:
  Color fillColor = checkpointColorFill;

  bool goal = false;
  bool saveCoins = true;
  bool saveKeys = true;

  bool shouldAnimate = true;
  bool animation = false;
  float animateTimer = 0, animateTime = 0.5f;

  void tick(Player* player) override;

  Checkpoint(Vector2 pos, bool goal, Level* level, int zLayer) : GameObject(Rectangle{pos.x, pos.y, 40.0f, 40.0f}, false, level, zLayer), goal(goal) {
    typeId = 8;
  };

  Checkpoint* clone() override;
  
  void serialize(std::ofstream& ofs) const override {
    GameObject::serialize(ofs);
    
    ofs.write((char*)&fillColor, sizeof(fillColor));
    ofs.write((char*)&goal, sizeof(goal));
    ofs.write((char*)&saveCoins, sizeof(saveCoins));
    ofs.write((char*)&saveKeys, sizeof(saveKeys));
  }
  
  void deserialize(std::ifstream& ifs) override {
    GameObject::deserialize(ifs);

    ifs.read((char*)&fillColor, sizeof(fillColor));
    ifs.read((char*)&goal, sizeof(goal));
    ifs.read((char*)&saveCoins, sizeof(saveCoins));
    ifs.read((char*)&saveKeys, sizeof(saveKeys));
  }
};

#endif
