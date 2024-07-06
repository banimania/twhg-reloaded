#include "buttonwidget.hpp"
#include <iostream>
#include <raylib.h>

void ButtonWidget::tick() {
  Widget::tick();

  if (hovered) {
    if (scale > maxScale) {
      scale = maxScale;
    } else if (scale < maxScale) {
      scale += scaleSpeed * GetFrameTime();
    }
  } else {
    if (scale > 1.0f) {
      scale -= scaleSpeed * GetFrameTime();
    } else if (scale < 1.0f) {
      scale = 1.0f;
    }
  }

  float difHalf = (rect.width * scale - rect.width) / 2.0f;
  DrawRectangleV({rect.x - difHalf, rect.y - difHalf}, {rect.width * scale, rect.height * scale}, borderColor);
  DrawRectangleGradientV(rect.x + borderThickness - difHalf, rect.y + borderThickness - difHalf, (rect.width - 2 * borderThickness) * scale, (rect.height - 2 * borderThickness) * scale, gradientColor1, gradientColor2);
}

void ButtonWidget::handleClick(int action, int mouseX, int mouseY) {
  Widget::handleClick(action, mouseX, mouseY);

  if (action == MOUSE_BUTTON_LEFT) func();
}
