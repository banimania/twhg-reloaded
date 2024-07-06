#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "../level/level.hpp"
#include <raylib.h>

class Editor {
public:
  Level* level;

  Camera2D camera;
  
  bool init = false;

  Editor() {
    level = new Level();
    
    camera.zoom = 0.8f;
    camera.rotation = 0.0f;
    camera.target = {-155, -80};
  }

  void tick();
  void initWidgets();
  
  void drawGrid();
};

#endif
