#include "widget.hpp"
#include "../utils/needed.hpp"

void Widget::tick() {
  if (!init) initWidget();

  hovered = (CheckCollisionPointRec({static_cast<float>(TWHGReloaded::mouse.x), static_cast<float>(TWHGReloaded::mouse.y)}, rect));

  if (hovered) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) handleClick(MOUSE_BUTTON_RIGHT, TWHGReloaded::mouse.x, TWHGReloaded::mouse.y);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) handleClick(MOUSE_BUTTON_LEFT, TWHGReloaded::mouse.x, TWHGReloaded::mouse.y);
    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) handleClick(MOUSE_BUTTON_MIDDLE, TWHGReloaded::mouse.x, TWHGReloaded::mouse.y);
  } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
    active = false;
  }
}

void Widget::handleClick(int action, int mouseX, int mouseY) {
  if (freeze) return;

  active = true;
}

void Widget::initWidget() {
  init = true;
}
