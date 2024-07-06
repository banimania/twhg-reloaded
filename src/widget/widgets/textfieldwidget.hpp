#ifndef TEXTFIELDWIDGET_HPP
#define TEXTFIELDWIDGET_HPP

#include "../widget.hpp"
#include "../../utils/colors.hpp"
#include "../../utils/fonts.hpp"
#include <cstddef>
#include <raylib.h>
#include <string>

class TextFieldWidget : public Widget {
public:
  Color borderColor = textFieldWidgetBorderColor;
  Color fillColor = textFieldWidgetFillColor;

  int borderThickness = 5;

  bool onlyNumbers;

  bool blink = false;
  float blinkTimer = 0, blinkTime = 0.5f;

  float backTimer = 0, backTime = 0.1f;

  std::string text = "";
  int maxLength;

  int fontSize;

  Font font;

  TextFieldWidget(Vector2 pos, float width, int fontSize, bool onlyNumbers, int maxLength) : Widget({pos.x, pos.y, width, fontSize + 10.0f}), fontSize(fontSize), text(""), onlyNumbers(onlyNumbers), maxLength(maxLength) {};

  void tick() override;

  void initWidget() override;
};

#endif
