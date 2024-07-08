#ifndef CONVEYOR_HPP
#define CONVEYOR_HPP

#include "../gameobject.hpp"
#include <unordered_map>

enum Direction {
  UP,
  DOWN,
  RIGHT,
  LEFT
};

class Conveyor : public GameObject {
public:
  float speed;
  Direction direction;

  bool isEditorSample = false;
  
  void drawArrow(Rectangle rect);
  void tick(Player* player) override;

  Conveyor(Vector2 pos, Direction direction, Level* level, int zLayer) : GameObject(Rectangle{pos.x, pos.y, 40.0f, 40.0f}, false, level, zLayer), speed(40.0f), direction(direction) {};
};

extern std::unordered_map<float, std::pair<float, float>> speedOffsetMap;

void tickConveyorManager();
std::pair<float, float> getConveyorOffsets(float speed);

#endif
