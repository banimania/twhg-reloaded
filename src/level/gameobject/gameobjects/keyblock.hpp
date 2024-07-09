#ifndef KEYBLOCK_HPP
#define KEYBLOCK_HPP

#include <raylib.h>
#include "../gameobject.hpp"
#include "../../../utils/colors.hpp"

class KeyBlock : public GameObject {
public:
  Color outlineColor = keyBlockColorOutline;
  Color fillColor = keyBlockColorFill;

  bool states[8] = {true, true, true, true, true, true, true, true};

  bool saved = false;

  int keyId;
  bool open = false;
  bool isOpening = false;
  float openTimer = 0.0f, openTime = 0.4f;

  int wallThickness = 5;

  void tick(Player* player) override;

  KeyBlock(Vector2 pos, int keyId, Level* level, int zLayer) : GameObject(Rectangle{pos.x, pos.y, 40.0f, 40.0f}, true, level, zLayer), keyId(keyId) {};
  
  void updateKeyBlock(std::vector<KeyBlock*> keyBlocks);

  KeyBlock* clone() override;
};

#endif
