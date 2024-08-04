#ifndef HUD_HPP
#define HUD_HPP

#include <raylib.h>
#include <string>

class Level;

std::string formatTime(float time);

class HUD {
public:
  void tick();
  void tickEditor();

  Level* level;

  HUD(Level* level) : level(level) {}
};

#endif
