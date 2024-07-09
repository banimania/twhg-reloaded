#ifndef CHECKPOINT_HPP
#define CHECKPOINT_HPP

#include <raylib.h>
#include "../gameobject.hpp"
#include "../../../utils/colors.hpp"

class Checkpoint : public GameObject {
public:
  Color fillColor = checkpointColorFill;

  bool goal = false;
  bool saveCoins = true;
  bool saveKeys = true;

  void tick(Player* player) override;

  Checkpoint(Vector2 pos, bool goal, Level* level, int zLayer) : GameObject(Rectangle{pos.x, pos.y, 40.0f, 40.0f}, false, level, zLayer), goal(goal) {};

  Checkpoint* clone() override;
};

#endif
