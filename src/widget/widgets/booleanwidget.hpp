#ifndef BOOLEANWIDGET_HPP
#define BOOLEANWIDGET_HPP

#include "../widget.hpp"
#include <string>

class BooleanWidget : public Widget {
public:
  std::string title;
  bool value;

  int fontSize;

  BooleanWidget(std::string title, bool value, Vector2 pos, int width, int fontSize) : Widget({pos.x, pos.y, (float) width, 40}), title(title), value(value), fontSize(fontSize) {};

  void tick() override;
  
  void handleClick(int action, int mouseX, int mouseY) override;
};

#endif
