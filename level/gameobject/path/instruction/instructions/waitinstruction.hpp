#ifndef WAITINSTRUCTION_HPP
#define WAITINSTRUCTION_HPP

#include "../instruction.hpp"

class WaitInstruction : public Instruction {
public:
  WaitInstruction(float time) : Instruction(time) {};
};

#endif
