#ifndef PATH_HPP
#define PATH_HPP

#include "instruction/instruction.hpp"
#include "instruction/instructions/circularinstruction.hpp"
#include "instruction/instructions/linealinstruction.hpp"
#include "instruction/instructions/waitinstruction.hpp"
#include <vector>
#include <fstream>

class GameObject;

class Path {
public:
  std::vector<Instruction*> instructions;
  int currentInstructionId = 0;

  Instruction* getCurrentInstruction();
  void tick();
  void updateObject(GameObject* gameObject);

  void removeInstruction(int instructionId);

  Path() {};
  
  void serialize(std::ofstream& ofs) const {
    int instructionsSize = instructions.size();
    ofs.write((char*)&instructionsSize, sizeof(instructionsSize));
    for (const auto& instruction : instructions) {
      int typeID = instruction->typeId;
      ofs.write((char*)&typeID, sizeof(typeID));
      instruction->serialize(ofs);
    }
  }

  void deserialize(std::ifstream& ifs) {
    int instructionsSize;
    ifs.read((char*)&instructionsSize, sizeof(instructionsSize));
    instructions.resize(instructionsSize);
    for (int i = 0; i < instructionsSize; ++i) {
      int typeID;
      ifs.read((char*)&typeID, sizeof(typeID));

      switch (typeID) {
        case 1:
          instructions[i] = new LinealInstruction({}, {});
          break;
        case 2:
          instructions[i] = new CircularInstruction({}, 0, 0);
          break;
        case 3:
          instructions[i] = new WaitInstruction(0);
          break;
      }
      instructions[i]->deserialize(ifs);
    }
  }
};
#endif
