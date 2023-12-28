#ifndef WALLBLOCK_HPP
#define WALLBLOCK_HPP

#include <raylib.h>
#include "../gameobject.hpp"
#include "../../../utils/colors.hpp"

class WallBlock : public GameObject {
public:
  Color outlineColor = wallBlockColorOutline, fillColor = wallBlockColorFill;
  
  void tick() override;

  WallBlock(float x, float y) : GameObject(x, y, 40.0f, 40.0f) {};
};

#endif
