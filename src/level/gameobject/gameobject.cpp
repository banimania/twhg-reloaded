#include "gameobject.hpp"
#include "../../utils/needed.hpp"

void GameObject::tick(Player* player) {
  if (TWHGReloaded::state == EDITOR) originalRect = rect;

  for (Path* path : paths) {
    path->updateObject(this);
  }
}
