#include "circularinstruction.hpp"

void CircularInstruction::calculateMovement() {

  if (!init) {
    radius = sqrt(pow(center.x, 2) + pow(center.y, 2));
    
    initialDegree = RAD2DEG * atan2(center.y, center.x);
    if (initialDegree < 0) initialDegree += 360;
    
    degreesMoved = initialDegree;

    init = true;
  }

  float deltaDegree = GetFrameTime() * angularSpeed;

  bool isLast = degreesMoved + deltaDegree >= degrees + initialDegree;

  float epx = radius * std::cos(DEG2RAD * degreesMoved);
  float epy = radius * std::sin(DEG2RAD * degreesMoved);
  
  degreesMoved += deltaDegree;
  if (isLast) degreesMoved = degrees + initialDegree;

  float ex = radius * std::cos(DEG2RAD * degreesMoved);
  float ey = radius * std::sin(DEG2RAD * degreesMoved);

  last = {epx - ex, epy - ey};

  if (isLast) {
    init = false;
    isDone = true;
    degreesMoved = initialDegree;
  }
}
