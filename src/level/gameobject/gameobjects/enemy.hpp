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

  Enemy(Vector2 pos, float radius, Level* level, int zLayer) : GameObject(Rectangle{pos.x - 10.0f, pos.y - 10.0f, 2.0f * radius, 2.0f * radius}, false, level, zLayer), radius(radius) {};

  Enemy* clone() override;
};

#endif
