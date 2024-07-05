#include "checkpoint.hpp"
#include <raylib.h>

void Checkpoint::tick(Player* player) {
  GameObject::tick(player);
  DrawRectangleRec(rect, checkpointColorFill);
}
