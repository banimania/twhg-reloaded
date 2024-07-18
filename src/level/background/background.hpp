#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <raylib.h>
#include "../../utils/constants.hpp"
#include "../../utils/colors.hpp"
#include <fstream>

enum BackgroundType { PLAIN, CHECKERBOARD };

class Background {
public:
  BackgroundType backgroundType;
  Color colorPrimary, colorSecondary;
  float squareSize;

  void tick(Camera2D camera);

  Background(BackgroundType backgroundType, Color colorPrimary, Color colorSecondary, float squareSize) : backgroundType(backgroundType), colorPrimary(colorPrimary), colorSecondary(colorSecondary), squareSize(squareSize) {};
  Background() : backgroundType(CHECKERBOARD), colorPrimary(backgroundColorPrimary), colorSecondary(backgroundColorSecondary), squareSize(40.0f) {};
  
  void serialize(std::ofstream& ofs) const {
    ofs.write((char*)&backgroundType, sizeof(backgroundType));
    ofs.write((char*)&colorPrimary, sizeof(colorPrimary));
    ofs.write((char*)&colorSecondary, sizeof(colorSecondary));
    ofs.write((char*)&squareSize, sizeof(squareSize));
  }

  void deserialize(std::ifstream& ifs) {
    ifs.read((char*)&backgroundType, sizeof(backgroundType));
    ifs.read((char*)&colorPrimary, sizeof(colorPrimary));
    ifs.read((char*)&colorSecondary, sizeof(colorSecondary));
    ifs.read((char*)&squareSize, sizeof(squareSize));
  }
};

#endif
