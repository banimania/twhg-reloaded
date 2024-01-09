#include "linealinstruction.hpp"

void LinealInstruction::tick(GameObject*& gameObject) {
  //TODO: fix inaccuracies with high-speed for low distances!
  Instruction::tick(gameObject);

  float dx = GetFrameTime() * speed.x * (movement.x > 0 ? 1 : -1);
  float dy = GetFrameTime() * speed.y * (movement.y > 0 ? 1 : -1);

  bool moveX = std::abs(movement.x) > std::abs(moved.x); 
  bool moveY = std::abs(movement.y) > std::abs(moved.y); 
  if (moveX) {
    gameObject->rect.x += dx;
    moved.x += dx;
  } else if (movement.x != moved.x) {
    float diffx = (std::max(movement.x, moved.x) - std::min(movement.x, moved.x)) * (dx > 0 ? 1 : -1);
    gameObject->rect.x += diffx;
  }
  if (moveY) {
    gameObject->rect.y += dy;
    moved.y += dy;
  } else if (movement.y != moved.y) {
    float diffy = (std::max(movement.y, moved.y) - std::min(movement.y, moved.y)) * (dy > 0 ? 1 : -1);
    gameObject->rect.y += diffy;
  }

  if (!moveX && !moveY) {
    isDone = true;
    moved = {0, 0};
  }
}
