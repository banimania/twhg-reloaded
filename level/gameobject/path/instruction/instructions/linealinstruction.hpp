#ifndef LINEALINSTRUCTION_HPP
#define LINEALINSTRUCTION_HPP

#include <math.h>
#include <raylib.h>
#include "../instruction.hpp"

class LinealInstruction : public Instruction {
public:
  Vector2 movement;
  float speed;

  void tick(GameObject*& gameObject) override;

  LinealInstruction(Vector2 movement, float speed) : Instruction(std::max(movement.x, movement.y) / speed), movement(movement), speed(speed) {};
};

#endif
