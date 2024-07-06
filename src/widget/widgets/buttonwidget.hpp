#ifndef BUTTONWIDGET_HPP
#define BUTTONWIDGET_HPP

#include "../widget.hpp"
#include "../../utils/colors.hpp"
#include <functional>

class ButtonWidget : public Widget {
public:
  Color borderColor = buttonWidgetBorderColor;
  Color gradientColor1 = buttonWidgetGradientColor1;
  Color gradientColor2 = buttonWidgetGradientColor2;

  int borderThickness = 5;

  float scale = 1.0f;
  float scaleSpeed = 1.0f;
  float maxScale = 1.1f;

  std::function<void()> func;

  ButtonWidget(Rectangle rect,  std::function<void()> func) : Widget(rect), func(func) {};

  void tick() override;

  void handleClick(int action, int mouseX, int mouseY) override;
};

#endif
