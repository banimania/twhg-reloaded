#include "conveyor.hpp"
#include <raylib.h>
#include <rlgl.h>
#include <unordered_map>
#include <utility>
#include <iostream>
#include "../../level.hpp"

void Conveyor::drawArrow(Rectangle rect) {
  rlBegin(RL_QUADS);

  rlColor4f(arrowColor.r / 255.0f, arrowColor.g / 255.0f, arrowColor.b / 255.0f, arrowColor.a / 255.0f);

  rlVertex2f(rect.x, rect.y);
  rlVertex2f(rect.x + (rect.width / 4) + 10, rect.y + rect.height / 2);
  rlVertex2f(rect.x + (rect.width / 2) + 20, rect.y + rect.height / 2);
  rlVertex2f(rect.x + 20, rect.y);

  rlVertex2f(rect.x + (rect.width / 4) + 10, rect.y + rect.height / 2);
  rlVertex2f(rect.x, rect.y + rect.height);
  rlVertex2f(rect.x + (rect.width / 4) + 10, rect.y + rect.height);
  rlVertex2f(rect.x + (rect.width / 2) + 20, rect.y + rect.height / 2);

  rlEnd();
}

void Conveyor::tick(Player* player) {
  GameObject::tick(player);
  
  //Background
  DrawRectangle(rect.x, rect.y, rect.width, rect.height, fillColor);

  int rotation = 0;

  switch (direction) {
    case UP:
      rotation = -90;
      break;
    case DOWN:
      rotation = 90;
      break;
    case LEFT:
      rotation = 180;
      break;
  }
  
  std::pair<float, float> offsets = getConveyorOffsets(speed);

  //Arrows
  Vector2 posScreen = GetWorldToScreen2D({rect.x, rect.y}, level->camera);
  Vector2 pos2Screen = GetWorldToScreen2D({rect.x + rect.width, rect.y + rect.height}, level->camera);
  Vector2 sizeScreen = {pos2Screen.x - posScreen.x, pos2Screen.y - posScreen.y};

  BeginScissorMode(isEditorSample ? rect.x : posScreen.x, isEditorSample ? rect.y : posScreen.y, isEditorSample ? rect.width : sizeScreen.x, isEditorSample ? rect.height : sizeScreen.y);
  rlPushMatrix();
  rlTranslatef(rect.x + rect.width / 2, rect.y + rect.height / 2, 0);
  rlRotatef(rotation, 0, 0, 1);
  rlTranslatef(-rect.x - rect.width / 2 + offsets.first, -rect.y - rect.height / 2, 0);
  drawArrow(rect);
  rlPopMatrix();

  rlPushMatrix();
  rlTranslatef(rect.x + rect.width / 2, rect.y + rect.height / 2, 0);
  rlRotatef(rotation, 0, 0, 1);
  rlTranslatef(-rect.x - rect.width / 2 + offsets.second, -rect.y - rect.height / 2, 0);
  drawArrow(rect);
  rlPopMatrix();

  //drawArrow({rect.x + offsets.first, rect.y, rect.width, rect.height});
  //drawArrow({rect.x + offsets.second, rect.y, rect.width, rect.height});
  
  EndScissorMode();
  
  //Player movement
  if (CheckCollisionRecs(rect, player->rect)) {
    float force = speed * GetFrameTime() * (direction == UP || direction == LEFT ? -1 : 1);
    if (player->force.x == 0 && player->force.y == 0) {
      (direction == RIGHT || direction == LEFT ? player->force.x : player->force.y) += force;
    } else {
      if (direction == RIGHT) {
        if (player->force.x > 0) {
          if (player->force.x >= force) return;
          else player->force.x = force;
        } else {
          player->force.x += force;
        }
      } else if (direction == DOWN) {
         if (player->force.y > 0) {
          if (player->force.y >= force) return;
          else player->force.y = force;
        } else {
          player->force.y += force;
        }
      } else if (direction == LEFT) {
        if (player->force.x < 0) {
          if (player->force.x <= force) return;
          else player->force.x = force;
        } else {
          player->force.x += force;
        }
      } else if (direction == UP) {
         if (player->force.y < 0) {
          if (player->force.y <= force) return;
          else player->force.y = force;
        } else {
          player->force.y += force;
        }
      }
    }
  }
}

Conveyor* Conveyor::clone() {
  Conveyor* clone = new Conveyor({rect.x, rect.y}, direction, level, zLayer);
  clone->rect = rect;
  clone->paths = paths;
  clone->speed = speed;
  return clone;
}
std::unordered_map<float, std::pair<float, float>> speedOffsetMap;

void tickConveyorManager() {
  for (std::pair<float, std::pair<float, float>> pair : speedOffsetMap) {
    float conveyorOffset = pair.second.first + pair.first * GetFrameTime();
    float conveyorOffset2 = pair.second.second + pair.first * GetFrameTime();

    if (conveyorOffset > 40) conveyorOffset = 0;
    if (conveyorOffset2 > 0) conveyorOffset2 = -40;

    auto it = speedOffsetMap.find(pair.first);
    if (it != speedOffsetMap.end()) {
      it->second = std::make_pair(conveyorOffset, conveyorOffset2);
    }
  }
}

std::pair<float, float> getConveyorOffsets(float speed) {
  if (speedOffsetMap.find(speed) == speedOffsetMap.end()) {
    speedOffsetMap.insert(std::make_pair(speed, std::make_pair(0.0f, -40.0f)));
  }

  for (std::pair<float, std::pair<float, float>> pair : speedOffsetMap) {
    if (speed == pair.first) return pair.second;
  }
}
