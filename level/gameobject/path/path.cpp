#include "path.hpp"
#include "../gameobject.hpp"

void Path::tick() {
  Instruction* currentInstruction = getCurrentInstruction();
  if (currentInstruction->isDone) {
    currentInstruction->isDone = false;
    currentInstructionId++;
    return;
  };

  currentInstruction->calculateMovement();
}

void Path::updateObject(GameObject* gameObject) {
  Instruction* currentInstruction = getCurrentInstruction();
  currentInstruction->tick(gameObject);
}

Instruction* Path::getCurrentInstruction() {
  if (instructions.empty()) return NULL;
  if (instructions.size() <= currentInstructionId) currentInstructionId = 0;

  return instructions[currentInstructionId];
}
