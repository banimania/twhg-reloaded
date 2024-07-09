#include "../level/level.hpp"
#include "../editor/editor.hpp"

enum GameState { MENU, EDITOR, PLAYING, PLAYTEST };

namespace TWHGReloaded {
  inline GameState state = EDITOR;
  inline Level level = Level();
  inline Editor editor = Editor();
}
