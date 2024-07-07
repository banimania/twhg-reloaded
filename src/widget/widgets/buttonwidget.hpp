#ifndef BUTTONWIDGET_HPP
#define BUTTONWIDGET_HPP

#include "../widget.hpp"
#include "../../utils/colors.hpp"
#include <functional>
#include <string>

class ButtonWidget : public Widget {
public:
  Color borderColor = buttonWidgetBorderColor;
  Color gradientColor1 = buttonWidgetGradientColor1;
  Color gradientColor2 = buttonWidgetGradientColor2;

  int borderThickness = 4;

  float scale = 1.0f;
  float scaleSpeed = 1.0f;
  float maxScale = 1.1f;

  std::string text;
  int fontSize;
  std::function<void()> func;

  bool selected = false;

  bool textured = false;
  float textureScale;
  std::string textureName;

  ButtonWidget(std::string text, int fontSize, Rectangle rect,  std::function<void()> func) : Widget(rect), fontSize(fontSize), func(func), text(text) {};
  ButtonWidget(std::string textureName, float textureScale, Rectangle rect,  std::function<void()> func) : Widget(rect), fontSize(fontSize), func(func), text(text), textured(true), textureName(textureName), textureScale(textureScale) {};

  void tick() override;

  void setSelected(bool selected);

  void handleClick(int action, int mouseX, int mouseY) override;
};

#endif
