#include "gameobject.hpp"

void GameObject::tick(Player* player) {
  for (Path* path : paths) {
    path->tick(this);
  }
}
