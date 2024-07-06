#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <raylib.h>
#include "../../utils/constants.hpp"
#include "../../utils/colors.hpp"

enum BackgroundType { PLAIN, CHECKERBOARD };

class Background {
public:
  BackgroundType backgroundType;
  Color colorPrimary, colorSecondary;
  float squareSize;

  void tick();

  Background(BackgroundType backgroundType, Color colorPrimary, Color colorSecondary, float squareSize) : backgroundType(backgroundType), colorPrimary(colorPrimary), colorSecondary(colorSecondary), squareSize(squareSize) {};
  Background() : backgroundType(CHECKERBOARD), colorPrimary(backgroundColorPrimary), colorSecondary(backgroundColorSecondary), squareSize(40.0f) {};
};

#endif
