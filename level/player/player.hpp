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

  void tick(Level* level);
  
  Player(Vector2 pos, float size, float speed) : rect(Rectangle{pos.x, pos.y, size, size}), speed(speed) {};
};

#endif
