#include "widget.hpp"
#include <raylib.h>

void Widget::tick() {
  if (!init) initWidget();

  hovered = (CheckCollisionPointRec({static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())}, rect));

  if (hovered) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) handleClick(MOUSE_BUTTON_RIGHT, GetMouseX(), GetMouseY());
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) handleClick(MOUSE_BUTTON_LEFT, GetMouseX(), GetMouseY());
    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) handleClick(MOUSE_BUTTON_MIDDLE, GetMouseX(), GetMouseY());
  } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
    active = false;
  }
}

void Widget::handleClick(int action, int mouseX, int mouseY) {
  active = true;
}

void Widget::initWidget() {
  init = true;
}
