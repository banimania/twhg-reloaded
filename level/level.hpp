#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "background/background.hpp"
#include "player/player.hpp"

class Level {
public:
  float startX, startY;
  Player player;
  Background background;

  void tick();

  Level(float startX, float startY, Player player, Background background) : startX(startX), startY(startY), player(player), background(background) {};
};

#endif
