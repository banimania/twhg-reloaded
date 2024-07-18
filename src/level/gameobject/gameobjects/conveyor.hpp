#ifndef CONVEYOR_HPP
#define CONVEYOR_HPP

#include "../gameobject.hpp"
#include <rlgl.h>
#include <unordered_map>

enum Direction {
  UP,
  DOWN,
  RIGHT,
  LEFT
};

class Conveyor : public GameObject {
public:
  Color fillColor = conveyorColorFill;
  Color arrowColor = conveyorColorArrow;

  float speed;
  Direction direction;

  bool isEditorSample = false;
  
  void drawArrow(Rectangle rect);
  void tick(Player* player) override;

  Conveyor(Vector2 pos, Direction direction, Level* level, int zLayer) : GameObject(Rectangle{pos.x, pos.y, 40.0f, 40.0f}, false, level, zLayer), speed(40.0f), direction(direction) {
    typeId = 7;
  };
  
  bool operator==(const Conveyor& other) const {
    return (speed == other.speed && direction == other.direction && arrowColor.r == other.arrowColor.r && arrowColor.g == other.arrowColor.g && arrowColor.b == other.arrowColor.b && arrowColor.a == other.arrowColor.a && fillColor.r == other.fillColor.r && fillColor.g == other.fillColor.g && fillColor.b == other.fillColor.b && fillColor.a == other.fillColor.a);
  }
  
  bool equals(const GameObject& other) const override {
    if (const Conveyor* o = dynamic_cast<const Conveyor*>(&other)) {
      return *this == *o;
    }
    return false;
  }

  Conveyor* clone() override;
  
  void serialize(std::ofstream& ofs) const override {
    GameObject::serialize(ofs);
    
    ofs.write((char*)&arrowColor, sizeof(arrowColor));
    ofs.write((char*)&fillColor, sizeof(fillColor));
    ofs.write((char*)&speed, sizeof(speed));
    ofs.write((char*)&direction, sizeof(direction));
  }
  
  void deserialize(std::ifstream& ifs) override {
    GameObject::deserialize(ifs);

    ifs.read((char*)&arrowColor, sizeof(arrowColor));
    ifs.read((char*)&fillColor, sizeof(fillColor));
    ifs.read((char*)&speed, sizeof(speed));
    ifs.read((char*)&direction, sizeof(direction));
  }
};

extern std::unordered_map<float, std::pair<float, float>> speedOffsetMap;

void tickConveyorManager();
std::pair<float, float> getConveyorOffsets(float speed);

#endif
