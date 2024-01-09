#ifndef LINEALINSTRUCTION_HPP
#define LINEALINSTRUCTION_HPP

#include <raylib.h>
#include "../instruction.hpp"
#include "../../../gameobject.hpp"
#include <cstdlib>

class LinealInstruction : public Instruction {
public:
  Vector2 movement, speed, moved = {0.0f, 0.0f};

  void tick(GameObject*& gameObject) override;

  LinealInstruction(Vector2 movement, Vector2 speed) : Instruction(), movement(movement), speed(speed) {};
};

#endif
