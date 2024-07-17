#ifndef INSTRUCTIONWIDGET_HPP
#define INSTRUCTIONWIDGET_HPP

#include "../widget.hpp"
#include "../../level/gameobject/path/path.hpp"
#include "buttonwidget.hpp"
#include "textfieldwidget.hpp"
#include <functional>
#include <memory>
#include "textfieldwidget.hpp"

class InstructionWidget : public Widget {
public:
  int instructionId;

  ButtonWidget removeButton;

  TextFieldWidget timeWidget;

  TextFieldWidget linealMovementWidgetX, linealMovementWidgetY, linealSpeedWidgetX, linealSpeedWidgetY;

  TextFieldWidget circularCenterWidgetX, circularCenterWidgetY, circularDegreesWidget, circularSpeedWidget; 
  
  InstructionWidget(Rectangle rect, int instructionId) : Widget(rect), timeWidget(TextFieldWidget("", {rect.x + 100, rect.y + 50}, 70, 35, true, 3)), linealMovementWidgetX(TextFieldWidget("", {rect.x + 105, rect.y + 50}, 85, 35, true, 4)), linealMovementWidgetY(TextFieldWidget("", {rect.x + 100 + 100, rect.y + 50}, 85, 35, true, 4)), linealSpeedWidgetX(TextFieldWidget("", {rect.x + 115, rect.y + 100}, 85, 35, true, 4)), linealSpeedWidgetY(TextFieldWidget("", {rect.x + 110 + 100, rect.y + 100}, 85, 35, true, 4)), instructionId(instructionId), circularCenterWidgetX(TextFieldWidget("", {rect.x + 115 + 5, rect.y + 50}, 85, 35, true, 4)), circularCenterWidgetY(TextFieldWidget("", {rect.x + 110 + 5 + 100, rect.y + 50}, 85, 35, true, 4)), circularDegreesWidget(TextFieldWidget("", {rect.x + 115 + 100 + 120 + 80, rect.y + 100}, 85, 35, true, 4)), circularSpeedWidget(TextFieldWidget("", {rect.x + 15 + 100, rect.y + 100}, 85, 35, true, 4)), removeButton(ButtonWidget("REMOVE", 35, {rect.x + rect.width - 140 - 10, rect.y + 5, 140, 60}, std::bind(&InstructionWidget::remove, this))) {
    timeWidget.maxNumber = 999;
    linealMovementWidgetX.maxNumber = 9999;
    linealMovementWidgetX.allowNegative = true;
    linealMovementWidgetY.maxNumber = 9999;
    linealMovementWidgetY.allowNegative = true;
    linealSpeedWidgetX.maxNumber = 9999;
    linealSpeedWidgetX.allowNegative = true;
    linealSpeedWidgetY.maxNumber = 9999;
    linealMovementWidgetY.allowNegative = true;

    circularCenterWidgetX.maxNumber = 999;
    circularCenterWidgetX.allowNegative = true;
    circularCenterWidgetY.maxNumber = 999;
    circularCenterWidgetY.allowNegative = true;
    circularDegreesWidget.maxNumber = 999;
    circularDegreesWidget.allowNegative = true;
    circularSpeedWidget.maxNumber = 999;
  };

  void tick() override;
  
  void handleClick(int action, int mouseX, int mouseY) override;

  void remove();
};

#endif
