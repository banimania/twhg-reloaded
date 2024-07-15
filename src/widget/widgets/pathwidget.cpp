#include "pathwidget.hpp"
#include "../../utils/colors.hpp"
#include <algorithm>
#include <string>
#include "../../utils/needed.hpp"

void PathWidget::tick() {
  Widget::tick();

  if (idWidget.text.empty() && !idWidget.active) idWidget.text = std::to_string(pathId);

  pathId = idWidget.text.empty() ? pathId : std::stoi(idWidget.text);

  DrawRectangleRec(rect, editorGradient2Color);
  DrawTextEx(hudFontBold, "Path ID:", {rect.x + 20, rect.y + 8}, 40, 0, WHITE);
  editButton.tick();
  removeButton.tick();
  idWidget.tick();
}

void PathWidget::handleClick(int action, int mouseX, int mouseY) {
  Widget::handleClick(action, mouseX, mouseY);

}

void PathWidget::edit() {

}

void PathWidget::remove() {
  TWHGReloaded::editor.pathWidgets.erase(std::find(TWHGReloaded::editor.pathWidgets.begin(), TWHGReloaded::editor.pathWidgets.end(), this));
}
