#include "buttonwidget.hpp"
#include <iostream>
#include <raylib.h>
#include "../../utils/fonts.hpp"
#include "../../utils/textures.hpp"

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

  if (freeze) scale = 1.0f;
  
  float difHalf = (rect.width * scale - rect.width) / 2.0f;

  DrawRectangleV({rect.x - difHalf, rect.y - difHalf}, {rect.width * scale, rect.height * scale}, borderColor);
  DrawRectangleGradientV(rect.x + borderThickness - difHalf, rect.y + borderThickness - difHalf, (rect.width - 2 * borderThickness) * scale, (rect.height - 2 * borderThickness) * scale, gradientColor1, gradientColor2);

  if (textured) {
    Texture tex = GetTextureFromName(textureName);
    float x = rect.x - difHalf + (rect.width * scale / 2.0f) - (tex.width * scale * textureScale / 2.0f);
    float y = rect.y - difHalf + (rect.height * scale / 2.0f) - (tex.height * scale * textureScale / 2.0f);
    DrawTextureEx(tex, {x, y}, 0.0f, textureScale * scale, WHITE);
    return;
  }

  DrawOutlinedCenteredText(hudFontBold, text.c_str(), {rect.x - difHalf, rect.y - difHalf, rect.width * scale, rect.height * scale}, fontSize * scale, WHITE, 2, BLACK);

  if (disabled) DrawRectangleV({rect.x - difHalf, rect.y - difHalf}, {rect.width * scale, rect.height * scale}, {0, 0, 0, 100});
}

void ButtonWidget::setSelected(bool selected) {
  this->selected = selected;
  borderColor = selected ? buttonWidgetSelectedBorderColor : buttonWidgetBorderColor;
}

void ButtonWidget::handleClick(int action, int mouseX, int mouseY) {
  Widget::handleClick(action, mouseX, mouseY);

  if (freeze || disabled) return;

  if (action == MOUSE_BUTTON_LEFT) func();
}
