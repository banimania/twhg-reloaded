#ifndef PATH_HPP
#define PATH_HPP

#include "instruction/instruction.hpp"
#include <vector>

class GameObject;

class Path {
public:
  std::vector<Instruction*> instructions;
  int currentInstructionId = 0;

  Instruction* getCurrentInstruction();
  void tick();
  void updateObject(GameObject* gameObject);

  Path() {};
};
#endif
