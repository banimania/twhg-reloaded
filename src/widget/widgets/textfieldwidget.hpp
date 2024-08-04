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

  bool onlyNumbers = false;

  bool allowNegative = false;

  bool menu = false;
  bool password = false;

  bool blink = false;
  float blinkTimer = 0, blinkTime = 0.5f;

  float backTimer = 0, backTime = 0.1f;

  std::string title;
  std::string text = "";
  int maxLength;
  int maxNumber = 0;

  int fontSize;

  Font font;

  TextFieldWidget(std::string title, Vector2 pos, float width, int fontSize, bool onlyNumbers, int maxLength) : Widget({pos.x, pos.y, width, fontSize + 10.0f}), fontSize(fontSize), text(""), onlyNumbers(onlyNumbers), maxLength(maxLength), title(title) {};

  void tick() override;

  void initWidget() override;
};

#endif
