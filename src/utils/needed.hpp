#include "../level/level.hpp"
#include "../editor/editor.hpp"
#include "../menu/menu.hpp"

enum GameState { MENU, EDITOR, PLAYING, PLAYTEST };

namespace TWHGReloaded {
  inline GameState state = MENU;
  inline Menu menu = Menu();
  inline Level level = Level();
  inline Editor editor = Editor(new Level());
  inline int master = 50;
  inline int music = 50;
  inline int effects = 50;
  inline Vector2 mouse = { 0 };
}
