#include "gameobject.hpp"
#include "../../utils/needed.hpp"

void GameObject::tick(Player* player) {
  if (level == nullptr) return;
  
  if (TWHGReloaded::state == EDITOR) {
    originalRect = rect;
    return;
  }

  for (int pathId : pathIds) {
    level->findPath(pathId)->updateObject(this);
  }
}
