#ifndef WALLBLOCK_HPP
#define WALLBLOCK_HPP

#include <raylib.h>
#include "../gameobject.hpp"
#include "../../../utils/colors.hpp"

class WallBlock : public GameObject {
public:
  Color outlineColor = wallBlockColorOutline, fillColor = wallBlockColorFill;
  
  void tick(Player player) override;

  WallBlock(Vector2 pos, Level* level) : GameObject(Rectangle{pos.x, pos.y, 40.0f, 40.0f}, true, level) {};
};

#endif
