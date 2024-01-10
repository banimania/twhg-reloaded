#ifndef CIRCULARINSTRUCTION_HPP
#define CIRCULARINSTRUCTION_HPP

#include <map>
#include <raylib.h>
#include "../instruction.hpp"
#include "../../../gameobject.hpp"

class CircularInstruction : public Instruction {
public:
  Vector2 center, originalCenter;
  float angularSpeed, degrees, degreesMoved = 0.0f, initialDegree = 0.0f;
  bool relative;

  std::map<GameObject*, float> radiusMap;
  std::map<GameObject*, Vector2> originalPositionsMap;

  void tick(GameObject*& gameObject) override;

  CircularInstruction(Vector2 center, float angularSpeed, float degrees, bool relative) : Instruction(), center(center), angularSpeed(angularSpeed), degrees(degrees), relative(relative) {};
};

#endif
