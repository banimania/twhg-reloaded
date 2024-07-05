#ifndef KEY_HPP
#define KEY_HPP

#include <raylib.h>
#include "../gameobject.hpp"
#include "../../../utils/textures.hpp"
#include "../../../utils/sounds.hpp"

class Key : public GameObject {
public:
  int keyId;

  bool collected = false;
  bool isBeingCollected = false;
  float collectTimer = 0.0f, collectTime = 0.4f;

  void tick(Player* player) override;

  Key(Vector2 pos, int keyId, Level* level) : GameObject(Rectangle{pos.x - 10.0f, pos.y - 10.0f, 20.0f, 20.0f}, false, level), keyId(keyId) {};
};

#endif
