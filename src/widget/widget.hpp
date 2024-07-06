#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <raylib.h>
class Widget {
public:
  Rectangle rect;

  bool visible = true;
  bool hovered = false;
  bool active = false;
  bool init = false;

  Widget(Rectangle rect) : rect(rect) {};

  virtual void tick();

  virtual void handleClick(int action, int mouseX, int mouseY);

  virtual void initWidget();
};

#endif
