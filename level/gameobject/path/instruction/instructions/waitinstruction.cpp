#include "waitinstruction.hpp"

void WaitInstruction::tick(GameObject*& gameObject) {
  Instruction::tick(gameObject);

  timer += GetFrameTime();

  if (timer >= time) {
    timer = 0;
    isDone = true;
  }
}
