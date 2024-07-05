#include "gameobject.hpp"

void GameObject::tick(Player* player) {
  for (Path* path : paths) {
    path->updateObject(this);
  }
}
