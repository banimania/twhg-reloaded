#include "../level/level.hpp"
#include "../editor/editor.hpp"

enum GameState { MENU, EDITOR, PLAYING };

namespace TWHGReloaded {
  GameState state = EDITOR;
  Level level = Level();
  Editor editor = Editor();
}
