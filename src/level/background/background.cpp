#include "background.hpp"
#include <raylib.h>
#include <string>

void Background::tick(Camera2D camera) {
  ClearBackground(colorPrimary);

  if (backgroundType == CHECKERBOARD) {

    int areaWidth = 1280;
    int areaHeight = 640;

    int ni = camera.target.x / areaWidth * (SCREEN_WIDTH / squareSize);
    int nj = camera.target.y / areaHeight * (SCREEN_HEIGHT / squareSize);

    for (int i = - 2 * (SCREEN_WIDTH / squareSize) - abs(ni); i <= (SCREEN_WIDTH / squareSize) * 2 + abs(ni); i++) {
      for (int j = - 2 * (SCREEN_HEIGHT / squareSize) - abs(nj); j <= (SCREEN_HEIGHT / squareSize) * 2 + abs(nj); j++) {
        if ((i + j) % 2 == 0) {
          DrawRectangle(i * squareSize, j * squareSize, squareSize, squareSize, colorSecondary);
        }
      }
    }
  }
}
