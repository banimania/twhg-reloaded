#include "linealinstruction.hpp"

void LinealInstruction::calculateMovement() {
  Vector2 oldMoved = moved;

  float dx = GetFrameTime() * speed.x * (movement.x > 0 ? 1 : -1);
  float dy = GetFrameTime() * speed.y * (movement.y > 0 ? 1 : -1);

  bool moveX = std::abs(movement.x) > std::abs(moved.x); 
  bool moveY = std::abs(movement.y) > std::abs(moved.y);
  if (moveX) {
    if (std::abs(movement.x) < std::abs(moved.x) + std::abs(dx)) dx = (std::max(movement.x, moved.x) - std::min(movement.x, moved.x)) * (dx > 0 ? 1 : -1);  
    moved.x += dx;
  }
  if (moveY) {
    if (std::abs(movement.y) < std::abs(moved.y) + std::abs(dy)) dy = (std::max(movement.y, moved.y) - std::min(movement.y, moved.y)) * (dy > 0 ? 1 : -1);
    moved.y += dy;
  }

  last = {moved.x - oldMoved.x, moved.y - oldMoved.y};

  if (!moveX && !moveY) {
    isDone = true;
    moved = {0.0f, 0.0f};
  }
}
