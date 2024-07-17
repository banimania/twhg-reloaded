#include "instructionwidget.hpp"
#include "../../utils/colors.hpp"
#include <algorithm>
#include <iostream>
#include <raylib.h>
#include <string>
#include "../../utils/needed.hpp"

void InstructionWidget::tick() {
  Widget::tick();

  DrawRectangleRec(rect, editorGradient2Color);
  std::string text = "";

  Instruction* instruction = TWHGReloaded::editor.level->findPath(TWHGReloaded::editor.pathEditing)->instructions[instructionId];

  if (LinealInstruction* linealInstruction = dynamic_cast<LinealInstruction*>(instruction)) {
    text = "Lineal Instruction";

    if (!linealMovementWidgetX.active) linealMovementWidgetX.text = std::to_string((int) linealInstruction->movement.x);
    if (!linealMovementWidgetY.active) linealMovementWidgetY.text = std::to_string((int) linealInstruction->movement.y);
    if (!linealSpeedWidgetX.active) linealSpeedWidgetX.text = std::to_string((int) linealInstruction->speed.x);
    if (!linealSpeedWidgetY.active) linealSpeedWidgetY.text = std::to_string((int) linealInstruction->speed.y);
    
    DrawTextEx(hudFont, "Move: ", {rect.x + 20, rect.y + 50}, 35, 0, WHITE);
    linealMovementWidgetX.tick();
    DrawTextEx(hudFont, ",", {linealMovementWidgetX.rect.x + linealMovementWidgetX.rect.width, rect.y + 50}, 35, 0, WHITE);
    linealMovementWidgetY.tick();
    DrawTextEx(hudFont, "m", {linealMovementWidgetY.rect.x + linealMovementWidgetY.rect.width + 2, rect.y + 50}, 35, 0, WHITE);
    
    DrawTextEx(hudFont, "Speed: ", {rect.x + 20, rect.y + 100}, 35, 0, WHITE);
    linealSpeedWidgetX.tick();
    DrawTextEx(hudFont, ",", {linealSpeedWidgetX.rect.x + linealSpeedWidgetX.rect.width, rect.y + 100}, 35, 0, WHITE);
    linealSpeedWidgetY.tick();
    DrawTextEx(hudFont, "m/s", {linealSpeedWidgetY.rect.x + linealMovementWidgetY.rect.width + 2, rect.y + 100}, 35, 0, WHITE);

    if ((linealMovementWidgetX.text.empty() || linealMovementWidgetX.text == "-") && !linealMovementWidgetX.active) linealMovementWidgetX.text = "40";
    if ((linealMovementWidgetY.text.empty() || linealMovementWidgetY.text == "-") && !linealMovementWidgetY.active) linealMovementWidgetY.text = "40";
    if ((linealSpeedWidgetX.text.empty() || linealSpeedWidgetX.text == "-") && !linealSpeedWidgetX.active) linealSpeedWidgetX.text = "40";
    if ((linealSpeedWidgetY.text.empty() || linealSpeedWidgetY.text == "-") && !linealSpeedWidgetY.active) linealSpeedWidgetY.text = "40";

    linealInstruction->movement = {linealMovementWidgetX.text.empty() || linealMovementWidgetX.text == "-" ? 40.0f : std::stoi(linealMovementWidgetX.text), linealMovementWidgetY.text.empty() || linealMovementWidgetY.text == "-" ? 40.0f : std::stoi(linealMovementWidgetY.text)};
    linealInstruction->speed = {linealSpeedWidgetX.text.empty() || linealSpeedWidgetX.text == "-" ? 40.0f : std::stoi(linealSpeedWidgetX.text), linealSpeedWidgetY.text.empty() || linealSpeedWidgetY.text == "-" ? 40.0f : std::stoi(linealSpeedWidgetY.text)};
  } else if (CircularInstruction* circularInstruction = dynamic_cast<CircularInstruction*>(instruction)) {
    text = "Circular Instruction";

    if (!circularCenterWidgetX.active) circularCenterWidgetX.text = std::to_string((int) circularInstruction->center.x);
    if (!circularCenterWidgetY.active) circularCenterWidgetY.text = std::to_string((int) circularInstruction->center.y);
    if (!circularDegreesWidget.active) circularDegreesWidget.text = std::to_string((int) circularInstruction->degrees);
    if (!circularSpeedWidget.active) circularSpeedWidget.text = std::to_string((int) circularInstruction->angularSpeed);

    DrawTextEx(hudFont, "Center: ", {rect.x + 20, rect.y + 50}, 35, 0, WHITE);
    circularCenterWidgetX.tick();
    DrawTextEx(hudFont, ",", {circularCenterWidgetX.rect.x + circularCenterWidgetX.rect.width, rect.y + 50}, 35, 0, WHITE);
    circularCenterWidgetY.tick();
    DrawTextEx(hudFont, "m", {circularCenterWidgetY.rect.x + circularCenterWidgetY.rect.width + 2, rect.y + 50}, 35, 0, WHITE);
    DrawTextEx(hudFont, "deg/s", {circularSpeedWidget.rect.x + circularSpeedWidget.rect.width + 2, rect.y + 100}, 35, 0, WHITE);

    DrawTextEx(hudFont, "Speed: ", {rect.x + 20, rect.y + 100}, 35, 0, WHITE);
    circularSpeedWidget.tick();

    DrawTextEx(hudFont, "Degrees: ", {circularSpeedWidget.rect.x + circularSpeedWidget.rect.width + 85, rect.y + 100}, 35, 0, WHITE);
    circularDegreesWidget.tick();

    if ((circularCenterWidgetX.text.empty() || circularCenterWidgetX.text == "-") && !circularCenterWidgetX.active) circularCenterWidgetX.text = "40";
    if ((circularCenterWidgetY.text.empty() || circularCenterWidgetY.text == "-") && !circularCenterWidgetY.active) circularCenterWidgetY.text = "40";
    if ((circularDegreesWidget.text.empty() || circularDegreesWidget.text == "-") && !circularDegreesWidget.active) circularDegreesWidget.text = "360";
    if ((circularSpeedWidget.text.empty() || circularSpeedWidget.text == "-") && !circularSpeedWidget.active) circularSpeedWidget.text = "400";

    circularInstruction->center = {circularCenterWidgetX.text.empty() || circularCenterWidgetX.text == "-" ? 40.0f : std::stoi(circularCenterWidgetX.text), circularCenterWidgetY.text.empty() || circularCenterWidgetY.text == "-" ? 40.0f : std::stoi(circularCenterWidgetY.text)};
    circularInstruction->degrees = circularDegreesWidget.text.empty() || circularDegreesWidget.text == "-" ? 360.0f : std::stoi(circularDegreesWidget.text);
    circularInstruction->angularSpeed = circularSpeedWidget.text.empty() || circularSpeedWidget.text == "-" ? 360.0f : std::stoi(circularSpeedWidget.text);
  } else if (WaitInstruction* waitInstruction = dynamic_cast<WaitInstruction*>(instruction)) {

    if (!timeWidget.active) timeWidget.text = std::to_string((int) waitInstruction->time);

    text = "Wait Instruction";
    
    DrawTextEx(hudFont, "Time: ", {rect.x + 20, rect.y + 50}, 35, 0, WHITE);
    timeWidget.tick();
    DrawTextEx(hudFont, "s", {timeWidget.rect.x + timeWidget.rect.width + 5, timeWidget.rect.y}, 35, 0, WHITE);
    
    if (timeWidget.text.empty() && !timeWidget.active) timeWidget.text = "1";
    
    waitInstruction->time = timeWidget.text.empty() ? 1 : std::stoi(timeWidget.text);
  }

  DrawTextEx(hudFontBold, text.c_str(), {rect.x + 20, rect.y + 8}, 40, 0, WHITE);
  removeButton.tick();
}

void InstructionWidget::handleClick(int action, int mouseX, int mouseY) {
  Widget::handleClick(action, mouseX, mouseY);

}

void InstructionWidget::remove() {
  TWHGReloaded::editor.instructionWidgets.erase(std::find(TWHGReloaded::editor.instructionWidgets.begin(), TWHGReloaded::editor.instructionWidgets.end(), this));
}
