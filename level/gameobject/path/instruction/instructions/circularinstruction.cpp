#include "circularinstruction.hpp"
#include <cmath>
#include <iostream>

void CircularInstruction::tick(GameObject*& gameObject) {
  Instruction::tick(gameObject);

  Vector2 originalPosition;
  if (originalPositionsMap.find(gameObject) == originalPositionsMap.end()) originalPositionsMap.insert(std::pair<GameObject*, Vector2>(gameObject, {gameObject->rect.x, gameObject->rect.y}));
  else originalPosition = originalPositionsMap.find(gameObject)->second;

  float radius = 0.0f;
  if (radiusMap.find(gameObject) == radiusMap.end()) {
    originalCenter = center;
    if (relative) {
      center.x += gameObject->rect.x;
      center.y += gameObject->rect.y;
    }
    radius = sqrt(pow(center.x - gameObject->rect.x, 2) + pow(center.y - gameObject->rect.y, 2));
    radiusMap.insert(std::pair<GameObject*, float>(gameObject, radius));

    initialDegree = RAD2DEG * atan2(gameObject->rect.y, gameObject->rect.x);
    degreesMoved = initialDegree;
  } else radius = radiusMap.find(gameObject)->second;

  float deltaDegree = GetFrameTime() * angularSpeed;
  float epx = radius * std::cos(DEG2RAD * degreesMoved);
  float epy = radius * std::sin(DEG2RAD * degreesMoved);
  degreesMoved += deltaDegree;
  float ex = radius * std::cos(DEG2RAD * degreesMoved);
  float ey = radius * std::sin(DEG2RAD * degreesMoved);

  float dx = epx - ex;
  float dy = epy - ey;

  if ((relative && originalCenter.x < 0) || (!relative && originalCenter.x < originalPosition.x)) dx = ex - epx;
  if ((relative && originalCenter.y < 0) || (!relative && originalCenter.y < originalPosition.y)) dy = ey - epy;

  gameObject->rect.x += dx;
  gameObject->rect.y += dy;

  if (degreesMoved >= degrees + initialDegree) {
    isDone = true;
    degreesMoved = initialDegree;
  }

  std::cout << degreesMoved << std::endl;
}
