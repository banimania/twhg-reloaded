#ifndef PATHWIDGET_HPP
#define PATHWIDGET_HPP

#include "../widget.hpp"
#include "../../level/gameobject/path/path.hpp"
#include "buttonwidget.hpp"
#include "textfieldwidget.hpp"
#include <functional>

class PathWidget : public Widget {
public:
  int pathId;

  ButtonWidget editButton;
  ButtonWidget removeButton;
  TextFieldWidget idWidget;

  PathWidget(Rectangle rect, int pathId) : Widget(rect), pathId(pathId), editButton(ButtonWidget("EDIT", 35, {rect.x + rect.width - 100 - 10, rect.y + 5, 100, rect.height - 10}, std::bind(&PathWidget::edit, this))), removeButton(ButtonWidget("REMOVE", 35, {rect.x + rect.width - 240 - 20, rect.y + 5, 140, rect.height - 10}, std::bind(&PathWidget::remove, this))), idWidget(TextFieldWidget("", {rect.x + 140, rect.y + 5}, 80, 44, true, 3)) {
    idWidget.maxNumber = 999;
  };

  void tick() override;
  
  void handleClick(int action, int mouseX, int mouseY) override;
  
  void edit();

  void remove();
};

#endif
