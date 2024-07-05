#ifndef CHECKPOINT_HPP
#define CHECKPOINT_HPP

#include <raylib.h>
#include "../gameobject.hpp"
#include "../../../utils/colors.hpp"

class Checkpoint : public GameObject {
public:
  void tick(Player* player) override;

  Checkpoint(Vector2 pos, Level* level) : GameObject(Rectangle{pos.x, pos.y, 40.0f, 40.0f}, false, level) {};
};

#endif
