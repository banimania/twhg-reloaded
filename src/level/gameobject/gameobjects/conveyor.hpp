#ifndef CONVEYOR_HPP
#define CONVEYOR_HPP

#include "../gameobject.hpp"

enum Direction {
  UP,
  DOWN,
  RIGHT,
  LEFT
};

class Conveyor : public GameObject {
public:
  float speed;
  Direction direction;

  void drawArrow(Rectangle rect);
  void tick(Player* player) override;

  Conveyor(Vector2 pos, Level* level) : GameObject(Rectangle{pos.x, pos.y, 40.0f, 40.0f}, false, level), speed(40.0f) {};
};

#endif
