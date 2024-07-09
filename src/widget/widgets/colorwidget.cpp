#include "colorwidget.hpp"
#include <raylib.h>
#include "../../utils/fonts.hpp"
#include "../../utils/colors.hpp"

void ColorWidget::tick() {
  Widget::tick();
  DrawRectangleRec({rect.x, rect.y, rect.width, 40}, {174, 174, 174, 255});
  DrawRectangleRec({rect.x + rect.width - 35, rect.y + 5, 30, 30}, color);

  DrawTextEx(hudFontBold, name.c_str(), {rect.x + 10, rect.y + 2}, 35, 0, RAYWHITE);

  redWidget.tick();
  greenWidget.tick();
  blueWidget.tick();

  if (redWidget.text.empty() && !redWidget.active) redWidget.text = std::to_string(color.r);
  if (greenWidget.text.empty() && !greenWidget.active) greenWidget.text = std::to_string(color.g);
  if (blueWidget.text.empty() && !blueWidget.active) blueWidget.text = std::to_string(color.b);

  color = {redWidget.text.empty() ? defaultColor.r : static_cast<unsigned char>(std::stoi(redWidget.text)), greenWidget.text.empty() ? defaultColor.g : static_cast<unsigned char>(std::stoi(greenWidget.text)), blueWidget.text.empty() ? defaultColor.b : static_cast<unsigned char>(std::stoi(blueWidget.text)), 255};
}
