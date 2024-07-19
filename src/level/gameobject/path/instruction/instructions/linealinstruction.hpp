#ifndef LINEALINSTRUCTION_HPP
#define LINEALINSTRUCTION_HPP

#include <raylib.h>
#include <cmath>
#include "../instruction.hpp"

class LinealInstruction : public Instruction {
public:
  Vector2 movement, speed, moved = {0.0f, 0.0f};

  void calculateMovement() override;

  void reset() override;

  LinealInstruction(Vector2 movement, Vector2 speed) : Instruction(), movement(movement), speed(speed) {
    typeId = 1;
  };
  
  void serialize(std::ofstream& ofs) const override {
    Instruction::serialize(ofs);
    ofs.write((char*)&movement, sizeof(movement));
    ofs.write((char*)&speed, sizeof(speed));
  }

  void deserialize(std::ifstream& ifs) override {
    Instruction::deserialize(ifs);
    ifs.read((char*)&movement, sizeof(movement));
    ifs.read((char*)&speed, sizeof(speed));
  }
};

#endif
