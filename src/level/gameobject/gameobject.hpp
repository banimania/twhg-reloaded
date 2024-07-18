#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <raylib.h>
#include "../player/player.hpp"
#include "path/path.hpp"
#include <fstream>

class GameObject {
public:
  Rectangle rect, originalRect;
  bool solid;
  Level* level;
  std::vector<Path*> paths;

  int zLayer;
  
  virtual void tick(Player* player);

  GameObject(Rectangle rect, bool solid, Level* level, int zLayer) : rect(rect), solid(solid), level(level), zLayer(zLayer), originalRect(rect) {};

  virtual GameObject* clone() = 0;

  int typeId = 0;

  virtual void serialize(std::ofstream& ofs) const {
    ofs.write((char*)&typeId, sizeof(typeId));

    ofs.write((char*)&rect, sizeof(rect));
    ofs.write((char*)&originalRect, sizeof(originalRect));
    ofs.write((char*)&solid, sizeof(solid));

    ofs.write((char*)&zLayer, sizeof(zLayer));
  }

  virtual void deserialize(std::ifstream& ifs) {
    ifs.read((char*)&rect, sizeof(rect));
    ifs.read((char*)&originalRect, sizeof(originalRect));
    ifs.read((char*)&solid, sizeof(solid));

    ifs.read((char*)&zLayer, sizeof(zLayer));
  }
};

#endif
