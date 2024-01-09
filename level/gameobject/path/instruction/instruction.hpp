#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <raylib.h>

class GameObject;

class Instruction {
public:
  bool isDone = false;

  virtual void tick(GameObject*& gameObject);

  Instruction() {};
};

#endif
