#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>
#include "../../utils/colors.hpp"

class Player {
public:
  float x, y, size, speed;
  Color outlineColor = playerColorOutline, fillColor = playerColorFill;

  void tick();
  
  Player(float x, float y, float size, float speed) : x(x), y(y), size(size), speed(speed) {};
};

#endif
