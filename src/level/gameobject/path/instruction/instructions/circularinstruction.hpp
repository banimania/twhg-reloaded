#ifndef CIRCULARINSTRUCTION_HPP
#define CIRCULARINSTRUCTION_HPP

#include <raylib.h>
#include <cmath>
#include "../instruction.hpp"

class CircularInstruction : public Instruction {
public:
  Vector2 center;
  float angularSpeed, degrees, degreesMoved = 0.0f, initialDegree, radius;
  bool init = false;

  void calculateMovement() override;

  CircularInstruction(Vector2 center, float angularSpeed, float degrees) : Instruction(), center(center), angularSpeed(angularSpeed), degrees(degrees) {};
};

#endif
