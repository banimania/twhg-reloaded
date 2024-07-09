#ifndef ENUMWIDGET_HPP
#define ENUMWIDGET_HPP

#include "../widget.hpp"
#include "../../utils/colors.hpp"
#include <string>
#include <vector>

class EnumWidget : public Widget {
public:
  Color borderColor = enumWidgetBorderColor;
  Color fillColor = enumWidgetFillColor;

  Font font;

  int borderThickness = 5;

  int fontSize;

  bool dropDown = false;

  std::string title;

  std::vector<std::string> options;
  std::string selectedOption;

  EnumWidget(std::string title, Vector2 pos, float width, int fontSize, std::vector<std::string> options, std::string selectedOption) : Widget({pos.x, pos.y, width, fontSize + 10.0f}), options(options), selectedOption(selectedOption), fontSize(fontSize), title(title) {};
  
  void tick() override;
  
  void handleClick(int action, int mouseX, int mouseY) override;

  void initWidget() override;
};

#endif
