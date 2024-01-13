#include "instruction.hpp"
#include "../../gameobject.hpp"

void Instruction::calculateMovement() {}
void Instruction::tick(GameObject*& gameObject) {
  gameObject->rect.x += last.x;
  gameObject->rect.y += last.y;
 
  //last = {0.0f, 0.0f}; is done in level.cpp for multi-object path support
  if (isDone) {
    gameObject->rect.x = (int) std::round(gameObject->rect.x);
    gameObject->rect.y = (int) std::round(gameObject->rect.y);
  }
}
