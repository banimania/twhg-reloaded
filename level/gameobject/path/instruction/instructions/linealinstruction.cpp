#include "linealinstruction.hpp"
#include "../../../gameobject.hpp"

void LinealInstruction::tick(GameObject*& gameObject) {
  Instruction::tick(gameObject);

  gameObject->rect.x += GetFrameTime() * (movement.x / time);
  gameObject->rect.y += GetFrameTime() * (movement.y / time);
}
