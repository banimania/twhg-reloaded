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

  void tick(Level* level);
  
  Player(Vector2 pos, float size, float speed) : rect(Rectangle{pos.x, pos.y, size, size}), speed(speed) {};
};

#endif
