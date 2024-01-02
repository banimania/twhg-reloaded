#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <raylib.h>
#include "../gameobject.hpp"
#include "../../../utils/colors.hpp"

class Enemy : public GameObject {
public:
  Color outlineColor = enemyColorOutline, fillColor = enemyColorFill;
  
  float radius = 10.0f;

  void tick(Player player) override;

  Enemy(Vector2 pos) : GameObject(Rectangle{pos.x - 10.0f, pos.y - 10.0f, 20.0f, 20.0f}, false) {};
};

#endif
