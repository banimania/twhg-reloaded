#ifndef HUD_HPP
#define HUD_HPP

#include <raylib.h>

class Level;

class HUD {
public:
  void tick();

  Level* level;

  HUD(Level* level) : level(level) {}
};

#endif
