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

  Coin(Vector2 pos, float radius, Level* level, int zLayer) : GameObject(Rectangle{pos.x - 10.0f, pos.y - 10.0f, 2.0f * radius, 2.0f * radius}, false, level, zLayer), radius(radius) {};

  Coin* clone() override;
};

#endif
