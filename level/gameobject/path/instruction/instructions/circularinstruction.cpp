#include "circularinstruction.hpp"
#include <cmath>

void CircularInstruction::tick(GameObject*& gameObject) {
  Instruction::tick(gameObject);

  float radius = 0.0f;
  if (radiusMap.find(gameObject) == radiusMap.end()) {
    if (relative) {
      center.x += gameObject->rect.x;
      center.y += gameObject->rect.y;
    }
    radius = sqrt(pow(center.x - gameObject->rect.x, 2) + pow(center.y - gameObject->rect.y, 2));
    radiusMap.insert(std::pair<GameObject*, float>(gameObject, radius));
  } else radius = radiusMap.find(gameObject)->second;

  float deltaDegree = GetFrameTime() * angularSpeed;
  float epx = radius * std::cos(DEG2RAD * degreesMoved);
  float epy = radius * std::sin(DEG2RAD * degreesMoved);
  degreesMoved += deltaDegree;
  float ex = radius * std::cos(DEG2RAD * degreesMoved);
  float ey = radius * std::sin(DEG2RAD * degreesMoved);

  float dx = ex - epx;
  float dy = ey - epy;

  gameObject->rect.x += dx;
  gameObject->rect.y += dy;

  if (degreesMoved >= degrees) {
    isDone = true;
    degreesMoved = 0.0f;
  }
}
