#ifndef FOG_HPP
#define FOG_HPP

#include <raylib.h>
#include "../gameobject.hpp"

class FogBlock : public GameObject {
public:

  bool visible = true;
  int radius = 100;

  void tick(Player* player) override;

  FogBlock(Vector2 pos, Level* level, int zLayer) : GameObject(Rectangle{pos.x, pos.y, 40.0f, 40.0f}, false, level, zLayer) {};

  FogBlock* clone() override;
};

#endif
