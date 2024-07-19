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
#include "gameobject/gameobjects/backgroundblock.hpp"
#include "gameobject/gameobjects/coin.hpp"
#include "gameobject/gameobjects/conveyor.hpp"
#include "gameobject/gameobjects/enemy.hpp"
#include "gameobject/gameobjects/fog.hpp"
#include "gameobject/gameobjects/key.hpp"
#include "gameobject/gameobjects/keyblock.hpp"
#include "gameobject/gameobjects/wallblock.hpp"
#include "gameobject/gameobjects/checkpoint.hpp"
#include "gameobject/path/path.hpp"
#include "gameobject/path/instruction/instructions/linealinstruction.hpp"
#include "gameobject/path/instruction/instructions/waitinstruction.hpp"
#include "gameobject/path/instruction/instructions/circularinstruction.hpp"
#include "hud/hud.hpp"
#include "player/player.hpp"
#include <fstream>

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
  int lowestEmptyPathId();

  void serialize(const std::string& filename) const {
    std::ofstream ofs(filename, std::ios::binary);
    ofs.write((char*)&startX, sizeof(startX));
    ofs.write((char*)&startY, sizeof(startY));

    size_t pathMapSize = pathMap.size();
    ofs.write((char*)&pathMapSize, sizeof(pathMapSize));
    for (const auto& pair : pathMap) {
      ofs.write((char*)&pair.first, sizeof(pair.first));
      pair.second->serialize(ofs);
    }

    size_t gameObjectsSize = gameObjects.size();
    ofs.write((char*)&gameObjectsSize, sizeof(gameObjectsSize));
    for (const auto& gameObject : gameObjects) {
      gameObject->serialize(ofs);
    }

    size_t nameLength = name.size();
    ofs.write((char*)&nameLength, sizeof(nameLength));
    ofs.write(name.c_str(), nameLength);

    background.serialize(ofs);

    ofs.write((char*)&freeCameraMode, sizeof(freeCameraMode));
    ofs.write((char*)&camGoalX, sizeof(camGoalX));
    ofs.write((char*)&camGoalY, sizeof(camGoalY));
    ofs.write((char*)&camMoveSpeed, sizeof(camMoveSpeed));
    ofs.close();
  }
  
  void deserialize(const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    ifs.read((char*)&startX, sizeof(startX));
    ifs.read((char*)&startY, sizeof(startY));

    size_t pathMapSize;
    ifs.read((char*)&pathMapSize, sizeof(pathMapSize));
    for (size_t i = 0; i < pathMapSize; ++i) {
      int key;
      ifs.read((char*)&key, sizeof(key));
      Path* path = new Path();
      path->deserialize(ifs);
      pathMap[key] = path;
    }
    
    size_t gameObjectsSize;
    ifs.read((char*)&gameObjectsSize, sizeof(gameObjectsSize));
    gameObjects.resize(gameObjectsSize, {});
    for (auto& gameObject : gameObjects) {
      int typeId;
      ifs.read((char*)&typeId, sizeof(typeId));

      if (typeId == 1) gameObject = new WallBlock({}, this, 0);
      else if (typeId == 2) gameObject = new BackgroundBlock({}, this, 0);
      else if (typeId == 3) gameObject = new Enemy({}, 10.0f, this, 0);
      else if (typeId == 4) gameObject = new Coin({}, 10.0f, this, 0);
      else if (typeId == 5) gameObject = new Key({}, 1, this, 0);
      else if (typeId == 6) gameObject = new KeyBlock({}, 1, this, 0);
      else if (typeId == 7) gameObject = new Conveyor({}, UP, this, 0);
      else if (typeId == 8) gameObject = new Checkpoint({}, false, this, 0);
      else if (typeId == 9) gameObject = new FogBlock({}, this, 0);

      gameObject->deserialize(ifs);
    }

    size_t nameLength;
    ifs.read((char*)&nameLength, sizeof(nameLength));
    name.resize(nameLength);
    ifs.read(&name[0], nameLength);

    background.deserialize(ifs);

    ifs.read((char*)&freeCameraMode, sizeof(freeCameraMode));
    ifs.read((char*)&camGoalX, sizeof(camGoalX));
    ifs.read((char*)&camGoalY, sizeof(camGoalY));
    ifs.read((char*)&camMoveSpeed, sizeof(camMoveSpeed));
    ifs.close();
  }
};

#endif
