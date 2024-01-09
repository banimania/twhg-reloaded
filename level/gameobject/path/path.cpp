#include "path.hpp"
#include "../gameobject.hpp"

void Path::tick(GameObject* gameObject) {
  if (instructions.empty()) return;
  if (instructions.size() <= currentInstructionId) currentInstructionId = 0;

  Instruction* currentInstruction = instructions[currentInstructionId];
  if (currentInstruction->isDone) {
    currentInstruction->isDone = false;
    currentInstructionId++;
    return;
  };

  currentInstruction->tick(gameObject);
}
