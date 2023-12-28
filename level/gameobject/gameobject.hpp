#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <raylib.h>
#include "../player/player.hpp"

class GameObject {
public:
  Rectangle rect;

  virtual void tick(Player player) {};

  GameObject(Rectangle rect) : rect(rect) {};
};

#endif
