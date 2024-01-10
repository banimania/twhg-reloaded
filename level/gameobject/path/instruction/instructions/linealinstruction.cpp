#include "linealinstruction.hpp"

void LinealInstruction::tick(GameObject*& gameObject) {
  Instruction::tick(gameObject);

  float dx = GetFrameTime() * speed.x * (movement.x > 0 ? 1 : -1);
  float dy = GetFrameTime() * speed.y * (movement.y > 0 ? 1 : -1);

  bool moveX = std::abs(movement.x) > std::abs(moved.x); 
  bool moveY = std::abs(movement.y) > std::abs(moved.y);
  if (moveX) {
    if (std::abs(movement.x) < std::abs(moved.x) + std::abs(dx)) dx = (std::max(movement.x, moved.x) - std::min(movement.x, moved.x)) * (dx > 0 ? 1 : -1);  
    gameObject->rect.x += dx;
    moved.x += dx;
  }
  if (moveY) {
    if (std::abs(movement.y) < std::abs(moved.y) + std::abs(dy)) dy = (std::max(movement.y, moved.y) - std::min(movement.y, moved.y)) * (dy > 0 ? 1 : -1);
    gameObject->rect.y += dy;
    moved.y += dy;
  }

  if (!moveX && !moveY) {
    isDone = true;
    moved = {0, 0};
  }
}
