#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <raylib.h>
#include "../gameobject.hpp"

class Enemy : public GameObject {
public:
  float radius;

  void tick(Player player) override;

  Enemy(Vector2 pos, float radius, Level* level) : GameObject(Rectangle{pos.x - 10.0f, pos.y - 10.0f, 2.0f * radius, 2.0f * radius}, false, level), radius(radius) {};
};

#endif
