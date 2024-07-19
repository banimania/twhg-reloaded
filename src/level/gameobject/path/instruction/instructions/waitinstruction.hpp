#ifndef WAITINSTRUCTION_HPP
#define WAITINSTRUCTION_HPP

#include <raylib.h>
#include "../instruction.hpp"

class WaitInstruction : public Instruction {
public:
  float time, timer = 0.0f;

  void tick(GameObject*& gameObject) override;

  void reset() override;

  WaitInstruction(float time) : Instruction(), time(time) {
    typeId = 3;
  };

  void serialize(std::ofstream& ofs) const override {
    Instruction::serialize(ofs);
    ofs.write((char*)&time, sizeof(time));
    ofs.write((char*)&timer, sizeof(timer));
  }

  void deserialize(std::ifstream& ifs) override {
    Instruction::deserialize(ifs);
    ifs.read((char*)&time, sizeof(time));
    ifs.read((char*)&timer, sizeof(timer));
  }
};

#endif
