#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <raylib.h>
#include <cmath>

class GameObject;

class Instruction {
public:
  bool isDone = false;
  Vector2 last = {0.0f, 0.0f};

  virtual void calculateMovement();
  virtual void tick(GameObject*& gameObject);
  virtual void reset();

  Instruction() {};
};

#endif
