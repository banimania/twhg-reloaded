#ifndef COLORWIDGET_HPP
#define COLORWIDGET_HPP

#include "../widget.hpp"
#include "textfieldwidget.hpp"
#include <string>

class ColorWidget : public Widget {
public:
  std::string name;
  Color color, defaultColor;

  TextFieldWidget redWidget, greenWidget, blueWidget;

  ColorWidget(std::string name, Color defaultColor, Vector2 pos, int width) : Widget({pos.x, pos.y, (float) width, 270}), name(name), color(defaultColor), defaultColor(defaultColor), redWidget(TextFieldWidget("Red", {pos.x + 10, pos.y + 75}, 220, 35, true, 3)), greenWidget(TextFieldWidget("Green", {pos.x + 10, pos.y + 150}, 220, 35, true, 3)), blueWidget(TextFieldWidget("Blue", {pos.x + 10, pos.y + 225}, 220, 35, true, 3)) {
    redWidget.maxNumber = 255;
    greenWidget.maxNumber = 255;
    blueWidget.maxNumber = 255;
  };

  void tick() override;
};

#endif
