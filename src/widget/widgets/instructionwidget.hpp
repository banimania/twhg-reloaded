#ifndef INSTRUCTIONWIDGET_HPP
#define INSTRUCTIONWIDGET_HPP

#include "../widget.hpp"
#include "../../level/gameobject/path/path.hpp"
#include "buttonwidget.hpp"
#include "textfieldwidget.hpp"
#include <functional>
#include <memory>

class InstructionWidget : public Widget {
public:
  int instructionId;

  ButtonWidget removeButton;

  InstructionWidget(Rectangle rect, int instructionId) : Widget(rect), instructionId(instructionId), removeButton(ButtonWidget("REMOVE", 35, {rect.x + rect.width - 140 - 10, rect.y + 5, 140, rect.height - 10}, std::bind(&InstructionWidget::remove, this))) {};

  void tick() override;
  
  void handleClick(int action, int mouseX, int mouseY) override;

  void remove();
};

#endif
