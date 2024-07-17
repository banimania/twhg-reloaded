#include "path.hpp"

void Path::tick() {
  if (instructions.empty()) return;

  Instruction* currentInstruction = getCurrentInstruction();
  if (currentInstruction->isDone) {
    currentInstruction->isDone = false;
    currentInstructionId++;
    return;
  };

  currentInstruction->calculateMovement();
}

void Path::updateObject(GameObject* gameObject) {
  if (instructions.empty()) return;

  Instruction* currentInstruction = getCurrentInstruction();
  currentInstruction->tick(gameObject);
}

Instruction* Path::getCurrentInstruction() {
  if (instructions.empty()) return nullptr;

  if (instructions.size() <= currentInstructionId) currentInstructionId = 0;

  return instructions[currentInstructionId];
}

void Path::removeInstruction(int instructionId) {
  if (instructionId < 0 || instructionId >= instructions.size()) return;
  delete instructions[instructionId];
  instructions.erase(instructions.begin() + instructionId);

  if (currentInstructionId == instructionId) {
    currentInstructionId--;
  }
}
