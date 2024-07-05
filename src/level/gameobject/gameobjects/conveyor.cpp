#include "conveyor.hpp"
#include <raylib.h>
#include <rlgl.h>

float conveyorOffset = 0;
float conveyorOffset2 = -40;

void Conveyor::drawArrow(Rectangle rect) {
  rlBegin(RL_QUADS);

  rlColor4f(conveyorColorArrow.r / 255.0f, conveyorColorArrow.g / 255.0f, conveyorColorArrow.b / 255.0f, conveyorColorArrow.a / 255.0f);

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
  DrawRectangle(rect.x, rect.y, rect.width, rect.height, conveyorColorFill);

  conveyorOffset += speed * GetFrameTime();
  conveyorOffset2 += speed * GetFrameTime();

  if (conveyorOffset > 40) conveyorOffset = 0;
  if (conveyorOffset2 > 0) conveyorOffset2 = -40;

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

  //Arrows
  BeginScissorMode(rect.x, rect.y, rect.width, rect.height);

  rlPushMatrix();
  rlTranslatef(rect.x + rect.width / 2, rect.y + rect.height / 2, 0);
  rlRotatef(rotation, 0, 0, 1);
  rlTranslatef(-rect.x - rect.width / 2 + conveyorOffset, -rect.y - rect.height / 2, 0);
  drawArrow(rect);
  rlPopMatrix();

  rlPushMatrix();
  rlTranslatef(rect.x + rect.width / 2, rect.y + rect.height / 2, 0);
  rlRotatef(rotation, 0, 0, 1);
  rlTranslatef(-rect.x - rect.width / 2 + conveyorOffset2, -rect.y - rect.height / 2, 0);
  drawArrow(rect);
  rlPopMatrix();
  
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
