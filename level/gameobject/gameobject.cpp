#include "gameobject.hpp"

void GameObject::tick(Player* player) {
  if (path) {
    path->tick(this);
  }
}
