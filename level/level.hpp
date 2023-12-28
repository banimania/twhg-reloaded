#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <raylib.h>
#include <vector>
#include "background/background.hpp"
#include "gameobject/gameobject.hpp"
#include "player/player.hpp"

class Level {
public:
  float startX, startY;
  Player player;
  std::vector<GameObject*> gameObjects;
  Background background;
  Camera2D camera = {{0, 0}, {0, 0}, 0.0f, 1.0f};

  void tick();

  Level(float startX, float startY, Player player, Background background) : startX(startX), startY(startY), player(player), background(background) {};
};

#endif
