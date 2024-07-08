#ifndef KEYBLOCK_HPP
#define KEYBLOCK_HPP

#include <raylib.h>
#include "../gameobject.hpp"
#include "../../../utils/colors.hpp"

class KeyBlock : public GameObject {
public:
  int keyId;
  bool open = false;
  bool isOpening = false;
  float openTimer = 0.0f, openTime = 0.4f;

  void tick(Player* player) override;

  KeyBlock(Vector2 pos, int keyId, Level* level, int zLayer) : GameObject(Rectangle{pos.x, pos.y, 40.0f, 40.0f}, true, level, zLayer), keyId(keyId) {};

  KeyBlock* clone() override;
};

#endif
