#ifndef BACKGROUNDBLOCK_HPP
#define BACKGROUNDBLOCK_HPP

#include <raylib.h>
#include "../gameobject.hpp"
#include "../../../utils/colors.hpp"

class BackgroundBlock : public GameObject {
public:
  void tick(Player* player) override;

  BackgroundBlock(Vector2 pos, Level* level) : GameObject(Rectangle{pos.x, pos.y, 40.0f, 40.0f}, true, level) {};
};

#endif