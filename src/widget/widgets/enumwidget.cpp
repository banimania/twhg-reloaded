#include "enumwidget.hpp"
#include <raylib.h>

void EnumWidget::tick() {
  Widget::tick();

  DrawRectangleRec(rect, borderColor);
  DrawRectangleRec({rect.x + borderThickness, rect.y + borderThickness, rect.width - borderThickness * 2, rect.height - borderThickness * 2}, fillColor);

  BeginScissorMode(rect.x, rect.y, rect.width, rect.height);
  DrawTextEx(font, selectedOption.c_str(), {rect.x + borderThickness + 1, rect.y + 2}, fontSize, 0, borderColor);
  DrawTriangle({rect.x + rect.width - 30, rect.y + borderThickness + 3}, {rect.x + rect.width - 20, rect.y + rect.height - borderThickness - 3}, {rect.x + rect.width - 10, rect.y + borderThickness + 3}, borderColor);
  EndScissorMode();
  
  if (dropDown) {
    int count = 0;
    for (std::string option : options) {
      if (selectedOption == option) continue;
      count++;
     
      Rectangle newRec = {rect.x, rect.y + count * rect.height, rect.width, rect.height};

      if (CheckCollisionPointRec({(float) GetMouseX(), (float) GetMouseY()}, newRec)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
          selectedOption = option;
          dropDown = false;
          break;
        }
      }

      Color selCol = {static_cast<unsigned char>(fillColor.r * 0.8), static_cast<unsigned char>(fillColor.g * 0.8), static_cast<unsigned char>(fillColor.b * 0.8), fillColor.a};
      DrawRectangleRec(newRec, CheckCollisionPointRec({(float) GetMouseX(), (float) GetMouseY()}, newRec) ? selCol : fillColor);
      DrawTextEx(font, option.c_str(), {rect.x + borderThickness + 1, rect.y + 2 + count * rect.height}, fontSize, 0, borderColor);
    }
  }
}

void EnumWidget::handleClick(int action, int mouseX, int mouseY) {
  Widget::handleClick(action, mouseX, mouseY);
  dropDown = !dropDown;
}

void EnumWidget::initWidget() {
  Widget::initWidget();

  font = LoadFontEx("./res/fonts/arial_bold.ttf", fontSize, NULL, 0);
  rect.height = MeasureTextEx(font, "W", fontSize, 0).y + 5;

}
