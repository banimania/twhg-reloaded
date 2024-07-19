#ifndef CIRCULARINSTRUCTION_HPP
#define CIRCULARINSTRUCTION_HPP

#include <raylib.h>
#include <cmath>
#include "../instruction.hpp"

class CircularInstruction : public Instruction {
public:
  Vector2 center;
  float angularSpeed, degrees, degreesMoved = 0.0f, initialDegree, radius;
  bool init = false;

  void calculateMovement() override;

  void reset() override;

  CircularInstruction(Vector2 center, float angularSpeed, float degrees) : Instruction(), center(center), angularSpeed(angularSpeed), degrees(degrees) {
    typeId = 2;
  };
  
  void serialize(std::ofstream& ofs) const override {
    Instruction::serialize(ofs);
    ofs.write((char*)&center, sizeof(center));
    ofs.write((char*)&angularSpeed, sizeof(angularSpeed));
    ofs.write((char*)&degrees, sizeof(degrees));
  }

  void deserialize(std::ifstream& ifs) override {
    Instruction::deserialize(ifs);
    ifs.read((char*)&center, sizeof(center));
    ifs.read((char*)&angularSpeed, sizeof(angularSpeed));
    ifs.read((char*)&degrees, sizeof(degrees));
  }
};

#endif
