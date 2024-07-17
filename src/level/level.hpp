#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <raylib.h>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <algorithm>
#include "background/background.hpp"
#include "gameobject/gameobject.hpp"
#include "gameobject/gameobjects/conveyor.hpp"
#include "gameobject/gameobjects/wallblock.hpp"
#include "gameobject/path/path.hpp"
#include "gameobject/path/instruction/instructions/linealinstruction.hpp"
#include "gameobject/path/instruction/instructions/waitinstruction.hpp"
#include "gameobject/path/instruction/instructions/circularinstruction.hpp"
#include "hud/hud.hpp"
#include "player/player.hpp"

class Level {
public:
  float startX, startY;
  float time = 0.0f;
  Player player;
  std::vector<GameObject*> gameObjects;
  std::string name;
  std::unordered_map<int, Path*> pathMap;
  Background background;
  Camera2D camera = {{0, 0}, {0, 0}, 0.0f, 1.0f};
  HUD hud = HUD(this);

  bool freeCameraMode = false;
  float camGoalX = 0, camGoalY = 0, camMoveSpeed = 500;

  void tick();

  void death();
  void reset();

  Level() : startX(125), startY(125), name("Unnamed"), player(Player()), background(Background()) {
    WallBlock* wallBlock = new WallBlock({200, 200}, this, 1);
    Path* path = new Path();
    path->instructions.push_back(new CircularInstruction({40, 40}, 400, 360));
    pathMap.insert(std::make_pair(0, path));
    wallBlock->paths.push_back(path);
    Path* path2 = new Path();
    path2->instructions.push_back(new LinealInstruction({40, 0}, {40, 40}));
    pathMap.insert(std::make_pair(1, path2));
    wallBlock->paths.push_back(path2);
    gameObjects.push_back(wallBlock);
  };

  Rectangle getObjectRectangle(std::vector<GameObject*> objects);

  template <typename T>
  std::vector<T*> getConsecutiveGameObjects(Vector2 pos) {
    std::vector<T*> result;
    std::vector<Vector2> positions = {pos};

    int i = 0;
    while (result.size() >= i) {
      Vector2 currentPos = positions.at(i);
      for (GameObject* gameObject : gameObjects) {
        if (T* object = dynamic_cast<T*>(gameObject)) {
          if ((CheckCollisionRecs({currentPos.x + 40, currentPos.y, 40, 40}, gameObject->rect))
          || (CheckCollisionRecs({currentPos.x, currentPos.y + 40, 40, 40}, gameObject->rect))
          || (CheckCollisionRecs({currentPos.x - 40, currentPos.y, 40, 40}, gameObject->rect))
          || (CheckCollisionRecs({currentPos.x, currentPos.y - 40, 40, 40}, gameObject->rect))
          ) {
            if (std::find(result.begin(), result.end(), object) == result.end()) {
              positions.push_back({gameObject->rect.x, gameObject->rect.y});
              result.push_back(object);
            }
          }
        }
      }
      i++;
    }

    return result;
  }

  template <typename T>
  std::vector<T*> getGameObjects() {
    std::vector<T*> result;

    for (GameObject* gameObject : gameObjects) {
      if (T* object = dynamic_cast<T*>(gameObject)) {
        result.push_back(object);
      }
    }

    return result;
  }

  int findPathId(Path* path);
  Path* findPath(int pathId);
  int highestEmptyPathId();
};

#endif
