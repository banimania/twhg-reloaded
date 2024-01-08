#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <raylib.h>

class GameObject;

class Instruction {
public:
  float time, timer = 0.0f;

  virtual void tick(GameObject*& gameObject);

  Instruction(float time) : time(time) {};
};

#endif
