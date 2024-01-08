#include "path.hpp"
#include "../gameobject.hpp"
#include "instruction/instructions/linealinstruction.hpp"

void Path::tick(GameObject* gameObject) {
  if (instructions.empty()) return;
  if (instructions.size() <= currentInstructionId) currentInstructionId = 0;

  Instruction* currentInstruction = instructions[currentInstructionId];
  if (currentInstruction->timer >= currentInstruction->time) {
    currentInstruction->timer = 0.0f;
    currentInstructionId++;
    
    //if (LinealInstruction* linealInstruction = dynamic_cast<LinealInstruction*>(currentInstruction));
    
    return;
  };

  currentInstruction->tick(gameObject);
}
