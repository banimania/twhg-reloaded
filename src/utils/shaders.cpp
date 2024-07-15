#include "shaders.hpp"
#include <raylib.h>

void loadShaders() {
  fogShader = LoadShader(0, TextFormat("res/shaders/fog.fs", 330));
}
