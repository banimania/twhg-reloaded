#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <raylib.h>
#include <string>
#include <vector>
#include <algorithm>
#include "background/background.hpp"
#include "gameobject/gameobject.hpp"
#include "hud/hud.hpp"
#include "player/player.hpp"

class Level {
public:
  float startX, startY;
  float time = 0.0f;
  Player player;
  std::vector<GameObject*> gameObjects;
  std::string name;
  Background background;
  Camera2D camera = {{0, 0}, {0, 0}, 0.0f, 1.0f};
  HUD hud = HUD(this);
 
  void tick();

  Level(float startX, float startY, std::string name, Player player, Background background) : startX(startX), startY(startY), name(name), player(player), background(background) {};
};

#endif
