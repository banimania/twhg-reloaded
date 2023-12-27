#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "background/background.hpp"
#include "player/player.hpp"
#include <raylib.h>

class Level {
public:
  float startX, startY;
  Player player;
  Background background;
  Camera2D camera = {{0, 0}, {0, 0}, 0.0f, 1.0f};

  void tick();

  Level(float startX, float startY, Player player, Background background) : startX(startX), startY(startY), player(player), background(background) {};
};

#endif
