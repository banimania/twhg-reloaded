#include "editor.hpp"
#include <cstddef>
#include <raylib.h>

#include "../widget/widgets/textfieldwidget.hpp"
#include "../widget/widgets/enumwidget.hpp"

TextFieldWidget textFieldWidget = TextFieldWidget({400, 400}, 100, 27, false, 5);
std::vector<std::string> options = std::vector<std::string>{"Up", "Down", "Right", "Left"};
EnumWidget enumWidget = EnumWidget({200, 200}, 120, 27, options, "Right");

void Editor::initWidgets() {
  init = true;
}

void Editor::tick() {
  ClearBackground(GRAY);

  if (!init) initWidgets();

  textFieldWidget.tick();

  enumWidget.tick();
}

