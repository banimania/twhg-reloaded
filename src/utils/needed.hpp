#include "../level/level.hpp"

enum GameState { MENU, EDITOR, PLAYING };

namespace TWHGReloaded {
  GameState state = PLAYING;
  Level level = Level(100, 100, "Level xd", Player({100, 100}, 30, 150), Background(CHECKERBOARD, backgroundColorPrimary, backgroundColorSecondary, 40.0f));
}
