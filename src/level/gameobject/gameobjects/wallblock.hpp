#ifndef WALLBLOCK_HPP
#define WALLBLOCK_HPP

#include <raylib.h>
#include "../gameobject.hpp"
#include "../../../utils/colors.hpp"

class WallBlock : public GameObject {
public:
  Color outlineColor = wallBlockColorOutline, fillColor = wallBlockColorFill;

  bool states[8] = {true, true, true, true, true, true, true, true};

  int wallThickness = 5;

  void tick(Player* player) override;

  void updateWallBlock(std::vector<WallBlock*> wallBlocks);

  WallBlock* clone() override;

  WallBlock(Vector2 pos, Level* level, int zLayer) : GameObject(Rectangle{pos.x, pos.y, 40.0f, 40.0f}, true, level, zLayer) {};
};

#endif
