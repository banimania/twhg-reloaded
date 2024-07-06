#include "textfieldwidget.hpp"
#include <cstddef>
#include <raylib.h>

void TextFieldWidget::tick() {
  Widget::tick();

  if (active) {
    blinkTimer += GetFrameTime();
    if (blinkTimer > blinkTime) {
      blinkTimer = 0;
      blink = !blink;
    }
  } else blink = false;

  DrawRectangleRec(rect, borderColor);
  DrawRectangleRec({rect.x + borderThickness, rect.y + borderThickness, rect.width - borderThickness * 2, rect.height - borderThickness * 2}, fillColor);

  if (active) {
    int keyPressed = GetCharPressed();
    if (keyPressed >= 32 && keyPressed < 126) {
      if (!(onlyNumbers && !isdigit(keyPressed)) && text.length() < maxLength) {
        text += (char) keyPressed;
      } 
    }

    backTimer += GetFrameTime();
    if (IsKeyDown(KEY_BACKSPACE) && backTimer > backTime) {
      backTimer = 0;
      text = text.substr(0, text.length() - 1);
    }
  }

  BeginScissorMode(rect.x, rect.y, rect.width, rect.height);
  DrawTextEx(font, text.c_str(), {rect.x + borderThickness + 1, rect.y + 2}, fontSize, 0, borderColor);
  if (blink) DrawRectangle(rect.x + MeasureTextEx(font, text.c_str(), fontSize, 0).x + borderThickness + 3, rect.y + borderThickness + 1, 3, rect.height - borderThickness * 2 - 2, borderColor);
  EndScissorMode();
}

void TextFieldWidget::initWidget() {
  Widget::initWidget();

  font = LoadFontEx("./res/fonts/arial_bold.ttf", fontSize, NULL, 0);
  rect.height = MeasureTextEx(font, "W", fontSize, 0).y + 5;

}
