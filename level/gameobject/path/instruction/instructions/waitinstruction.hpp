#ifndef WAITINSTRUCTION_HPP
#define WAITINSTRUCTION_HPP

#include <raylib.h>
#include "../instruction.hpp"

class WaitInstruction : public Instruction {
public:
  float time, timer = 0.0f;

  void tick(GameObject*& gameObject) override;

  WaitInstruction(float time) : Instruction(), time(time) {};
};

#endif
