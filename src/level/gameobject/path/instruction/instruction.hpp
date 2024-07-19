#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <raylib.h>
#include <cmath>
#include <fstream>

class GameObject;

class Instruction {
public:
  bool isDone = false;
  Vector2 last = {0.0f, 0.0f};

  virtual void calculateMovement();
  virtual void tick(GameObject*& gameObject);
  virtual void reset();

  int typeId = 0;

  Instruction() {};
  
  virtual void serialize(std::ofstream& ofs) const {}
  virtual void deserialize(std::ifstream& ifs) {}
};

#endif
