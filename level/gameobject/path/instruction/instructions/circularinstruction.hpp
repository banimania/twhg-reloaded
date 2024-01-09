#ifndef CIRCULARINSTRUCTION_HPP
#define CIRCULARINSTRUCTION_HPP

#include <raylib.h>
#include "../instruction.hpp"

class CircularInstruction : public Instruction {
public:
  Vector2 center;
  float angularSpeed;

  void tick(GameObject*& gameObject) override;

  CircularInstruction(Vector2 center, float angularSpeed) : Instruction(), center(center), angularSpeed(angularSpeed) {};
};

#endif
