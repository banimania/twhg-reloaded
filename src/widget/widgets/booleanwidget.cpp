#include "booleanwidget.hpp"
#include "../../utils/colors.hpp"
#include "../../utils/fonts.hpp"
#include "../../utils/needed.hpp"
#include <raylib.h>

void BooleanWidget::tick() {
  Widget::tick();

  DrawTextEx(hudFontBold, title.c_str(), {rect.x + 10, rect.y}, fontSize, 0, textFieldWidgetBorderColor);

  DrawRectangleRec({rect.x + rect.width - 30, rect.y + 5, 25, 25}, textFieldWidgetBorderColor);
  DrawRectangleRec({rect.x + rect.width - 30 + 5, rect.y + 5 + 5, 25 - 10, 25 - 10}, editorUIColor);

  if (value) DrawRectangleRec({rect.x + rect.width - 30 + 7, rect.y + 5 + 7, 25 - 14, 25 - 14}, textFieldWidgetBorderColor);
}

void BooleanWidget::handleClick(int action, int mouseX, int mouseY) {
  Widget::handleClick(action, mouseX, mouseY);

  if (freeze) return;

  if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    if (CheckCollisionPointRec(TWHGReloaded::mouse,  {rect.x + rect.width - 30, rect.y + 5, 25, 25})) value = !value;
  }
}
