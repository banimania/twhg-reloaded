#include "background.hpp"

void Background::tick() {
  ClearBackground(colorPrimary);

  if (backgroundType == CHECKERBOARD) {
    for (int i = 0; i < SCREEN_WIDTH / squareSize; i++) {
      for (int j = 0; j < SCREEN_HEIGHT / squareSize; j++) {
        if ((i + j) % 2 == 0) DrawRectangle(i * squareSize, j * squareSize, squareSize, squareSize, colorSecondary);
      }
    }
  }
}
