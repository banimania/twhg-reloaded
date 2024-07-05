#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>
#include "../../utils/colors.hpp"

class Level;

class Player {
public:
  Rectangle rect;
  float speed;
  Color outlineColor = playerColorOutline, fillColor = playerColorFill;

  bool isDying = false;
  float dyingTimer = 0.0f, dyingTime = 0.5f;

  int deaths = 0;

  Vector2 force = {0, 0};

  void tick(Level* level);
  void die();

  Player(Vector2 pos, float size, float speed) : rect(Rectangle{pos.x, pos.y, size, size}), speed(speed) {};
};

#endif
