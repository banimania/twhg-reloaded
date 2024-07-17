#include "instructionwidget.hpp"
#include "../../utils/colors.hpp"
#include <algorithm>
#include <string>
#include "../../utils/needed.hpp"

void InstructionWidget::tick() {
  Widget::tick();

  DrawRectangleRec(rect, editorGradient2Color);
  std::string text = "";

  Instruction* instruction = TWHGReloaded::editor.level->findPath(TWHGReloaded::editor.pathEditing)->instructions[instructionId];

  if (LinealInstruction* linealInstruction = dynamic_cast<LinealInstruction*>(instruction)) {
    text = "Lineal Instruction";
  } else if (CircularInstruction* circularInstruction = dynamic_cast<CircularInstruction*>(instruction)) {
    text = "Circular Instruction";
  } else if (WaitInstruction* waitInstruction = dynamic_cast<WaitInstruction*>(instruction)) {
    text = "Wait Instruction";
  }

  DrawTextEx(hudFontBold, text.c_str(), {rect.x + 20, rect.y + 8}, 40, 0, WHITE);
  removeButton.tick();
}

void InstructionWidget::handleClick(int action, int mouseX, int mouseY) {
  Widget::handleClick(action, mouseX, mouseY);

}

void InstructionWidget::remove() {
  //TWHGReloaded::editor.instructionWidgets.erase(std::find(TWHGReloaded::editor.instructionWidgets.begin(), TWHGReloaded::editor.instructionWidgets.end(), this));
  TWHGReloaded::editor.level->findPath(TWHGReloaded::editor.pathEditing)->instructions.erase(std::find(TWHGReloaded::editor.level->findPath(TWHGReloaded::editor.pathEditing)->instructions.begin(), TWHGReloaded::editor.level->findPath(TWHGReloaded::editor.pathEditing)->instructions.end(), TWHGReloaded::editor.level->findPath(TWHGReloaded::editor.pathEditing)->instructions[instructionId]));
  TWHGReloaded::editor.instructionsInit = false;
}
