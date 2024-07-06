#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "../level/level.hpp"

class Editor {
public:
  Level* level;

  bool init = false;

  Editor() {
    level = new Level();
  }

  void tick();
  void initWidgets();
};

#endif
