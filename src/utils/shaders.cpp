#include "shaders.hpp"
#include <raylib.h>

#if defined(__EMSCRIPTEN__)
  #define GLSL_VERSION 100
#else
  #define GLSL_VERSION 330
#endif

void loadShaders() {
  fogShader = LoadShader(0, TextFormat("res/shaders/fog%i.fs", GLSL_VERSION));
  distortionShader = LoadShader(0, TextFormat("res/shaders/distortion%i.fs", GLSL_VERSION));
}
