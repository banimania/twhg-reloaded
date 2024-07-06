#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <raylib.h>
#include "../player/player.hpp"
#include "path/path.hpp"

class GameObject {
public:
  Rectangle rect;
  bool solid;
  Level* level;
  std::vector<Path*> paths;

  virtual void tick(Player* player);

  GameObject(Rectangle rect, bool solid, Level* level) : rect(rect), solid(solid), level(level) {};
};

#endif