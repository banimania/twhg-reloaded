#ifndef COIN_HPP
#define COIN_HPP

#include <raylib.h>
#include "../gameobject.hpp"
#include "../../../utils/textures.hpp"
#include "../../../utils/sounds.hpp"

class Coin : public GameObject {
public:
  float radius;

  bool collected = false;
  bool isBeingCollected = false;
  float collectTimer = 0.0f, collectTime = 0.4f;

  void tick(Player* player) override;

  Coin(Vector2 pos, float radius, Level* level) : GameObject(Rectangle{pos.x - 10.0f, pos.y - 10.0f, 2.0f * radius, 2.0f * radius}, false, level), radius(radius) {};
};

#endif
